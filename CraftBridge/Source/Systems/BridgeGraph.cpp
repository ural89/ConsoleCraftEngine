#include "BridgeGraph.h"
#include "Terrain.h"
#include "Deck.h"
#include "PolygonFactory.h"
#include "../BridgeConfig.h"
#include "Core/LineDrawer.h"
#include "Core/Physics/Polygon/Polygon.h"
#include "Core/Physics/Polygon/PolygonCreator/PolygonCreator.h"
#include "Core/Physics/Polygon/JointCreator.h"
#include "Core/Scene.h"
#include <cmath>

BridgeGraph::BridgeGraph(Scene &scene, PolygonCreator &polygonCreator, JointCreator &jointCreator)
    : scene(scene), polygonCreator(polygonCreator), jointCreator(jointCreator)
{
    previewDrawer = new LineDrawer(scene);
    previewDrawer->CreateLineParticles(PREVIEW_GLYPHS, PREVIEW_COLOR);
}

BridgeGraph::~BridgeGraph()
{
    Teardown();
    previewDrawer->ClearLines();
    delete previewDrawer;
    previewDrawer = nullptr;
}

void BridgeGraph::Reset(float newBudget)
{
    Teardown();
    nodes.clear();
    beams.clear();
    pendingNode = -1;
    spent = 0.f;
    budget = newBudget;
    frozen = true;
}

int BridgeGraph::FindNearestNode(Vector2 pos) const
{
    int best = -1;
    float bestDist = NODE_SNAP_RADIUS;
    for (size_t i = 0; i < nodes.size(); i++)
    {
        if (!nodes[i].alive)
            continue;
        float d = Vector2::Distance(nodes[i].position, pos);
        if (d <= bestDist)
        {
            bestDist = d;
            best = static_cast<int>(i);
        }
    }
    return best;
}

int BridgeGraph::FindNearestDeckSegment(Vector2 pos, Deck &deck) const
{
    int best = -1;
    float bestDist = NODE_SNAP_RADIUS;
    for (int i = 0; i < deck.SegmentCount(); i++)
    {
        float d = Vector2::Distance(deck.SegmentPosition(i), pos);
        if (d <= bestDist)
        {
            bestDist = d;
            best = i;
        }
    }
    return best;
}

int BridgeGraph::FindOrCreateNode(Vector2 pos, Terrain &terrain, Deck &deck)
{
    int existing = FindNearestNode(pos);
    if (existing >= 0)
        return existing;

    BridgeNode node;
    node.position = pos;

    if (terrain.NearLeft(pos))
    {
        node.anchor = AnchorKind::TerrainLeft;
        node.position.Y = terrain.GroundY();
    }
    else if (terrain.NearRight(pos))
    {
        node.anchor = AnchorKind::TerrainRight;
        node.position.Y = terrain.GroundY();
    }
    else if (terrain.NearPillar(pos))
    {
        node.anchor = AnchorKind::Pillar;
    }
    else
    {
        int segment = FindNearestDeckSegment(pos, deck);
        if (segment >= 0)
        {
            node.anchor = AnchorKind::Deck;
            node.deckSegmentIndex = segment;
            node.position = deck.SegmentPosition(segment);
        }
    }

    nodes.push_back(node);
    int idx = static_cast<int>(nodes.size()) - 1;
    InstantiateNode(idx, terrain, deck);
    return idx;
}

b2Body *BridgeGraph::ResolveAnchorBody(const BridgeNode &node, Terrain &terrain, Deck &deck) const
{
    switch (node.anchor)
    {
    case AnchorKind::TerrainLeft:
        return terrain.LeftBody();
    case AnchorKind::TerrainRight:
        return terrain.RightBody();
    case AnchorKind::Pillar:
        return terrain.PillarBody();
    case AnchorKind::Deck:
        return deck.SegmentBody(node.deckSegmentIndex);
    default:
        return nullptr;
    }
}

void BridgeGraph::InstantiateNode(int idx, Terrain &terrain, Deck &deck)
{
    BridgeNode &node = nodes[idx];
    if (!node.alive)
        return;

    // An anchored node is not a shape of its own: it is a named point on
    // whichever cliff/pillar/plank body exists *now*, which is a different
    // body after every teardown.
    if (node.anchor != AnchorKind::None)
    {
        node.body = ResolveAnchorBody(node, terrain, deck);
        return;
    }

    node.polygon = PolygonFactory::CreateBox(polygonCreator, node.position, Vector2(NODE_SIZE, NODE_SIZE), 0.f,
                                             NODE_COLOR, NODE_GLYPHS);
    PolygonFactory::SetPhysics(node.polygon, BEAM_DENSITY, BEAM_FRICTION, BRIDGE_GROUP, CATEGORY_BRIDGE, MASK_BRIDGE);
    PolygonFactory::SetStatic(node.polygon, frozen);
    // A node box is under a console cell across, so its corner markers are the
    // only thing that renders it at all.
    PolygonFactory::PrepareCorners(node.polygon, true);
    node.body = node.polygon->GetBody();
}

void BridgeGraph::InstantiateBeam(int idx)
{
    BridgeBeam &beam = beams[idx];
    if (beam.removed)
        return;

    Vector2 p0 = nodes[beam.a].position;
    Vector2 p1 = nodes[beam.b].position;
    float length = Vector2::Distance(p0, p1);
    Vector2 center = (p0 + p1) * 0.5f;
    float angleDegrees = std::atan2(p1.Y - p0.Y, p1.X - p0.X) * (180.0f / 3.14159265f);

    beam.polygon = PolygonFactory::CreateBox(polygonCreator, center, Vector2(length, BEAM_THICKNESS), angleDegrees,
                                             BEAM_OK_COLOR, BEAM_GLYPHS);
    PolygonFactory::SetPhysics(beam.polygon, BEAM_DENSITY, BEAM_FRICTION, BRIDGE_GROUP, CATEGORY_BRIDGE, MASK_BRIDGE);
    PolygonFactory::SetStatic(beam.polygon, frozen);
    PolygonFactory::PrepareCorners(beam.polygon, false);

    beam.jointA = jointCreator.CreateRevoluteJoint(nodes[beam.a].body, beam.polygon->GetBody(), p0);
    beam.jointB = jointCreator.CreateRevoluteJoint(nodes[beam.b].body, beam.polygon->GetBody(), p1);

    beam.broken = false;
    beam.stress = 0.f;
    beam.shownColor = BEAM_OK_COLOR;
}

bool BridgeGraph::AddBeam(int a, int b, std::string &message)
{
    if (a < 0 || b < 0 || a == b || a >= static_cast<int>(nodes.size()) || b >= static_cast<int>(nodes.size()) ||
        !nodes[a].alive || !nodes[b].alive)
    {
        message = "Invalid beam";
        return false;
    }

    float length = Vector2::Distance(nodes[a].position, nodes[b].position);
    if (length < MIN_BEAM_LENGTH)
    {
        message = "Too short";
        return false;
    }
    if (length > MAX_BEAM_LENGTH)
    {
        message = "Too long - split it with a node";
        return false;
    }

    for (const BridgeBeam &beam : beams)
    {
        if (beam.removed)
            continue;
        if ((beam.a == a && beam.b == b) || (beam.a == b && beam.b == a))
        {
            message = "Beam already there";
            return false;
        }
    }

    float cost = length * COST_PER_UNIT;
    if (spent + cost > budget + 0.001f)
    {
        message = "Not enough budget";
        return false;
    }

    BridgeBeam beam;
    beam.a = a;
    beam.b = b;
    beam.cost = cost;
    beams.push_back(beam);
    int idx = static_cast<int>(beams.size()) - 1;
    InstantiateBeam(idx);
    spent += cost;

    message = "Beam placed ($" + std::to_string(static_cast<int>(cost)) + ")";
    return true;
}

void BridgeGraph::DestroyBeamPhysics(BridgeBeam &beam)
{
    // The shape owns the joints: destroying its body destroys both hinges, so
    // they must not be destroyed separately (that would be a double free).
    PolygonFactory::Destroy(scene, beam.polygon);
    beam.jointA = nullptr;
    beam.jointB = nullptr;
}

int BridgeGraph::NodeActiveBeamCount(int nodeIdx) const
{
    int count = 0;
    for (const BridgeBeam &beam : beams)
    {
        if (beam.removed)
            continue;
        if (beam.a == nodeIdx || beam.b == nodeIdx)
            count++;
    }
    return count;
}

bool BridgeGraph::RemoveNearestBeam(Vector2 pos, std::string &message)
{
    int best = -1;
    float bestDist = BEAM_DELETE_RADIUS;

    for (size_t i = 0; i < beams.size(); i++)
    {
        if (beams[i].removed)
            continue;
        Vector2 mid = (nodes[beams[i].a].position + nodes[beams[i].b].position) * 0.5f;
        float d = Vector2::Distance(mid, pos);
        if (d <= bestDist)
        {
            bestDist = d;
            best = static_cast<int>(i);
        }
    }

    if (best < 0)
    {
        message = "No beam nearby";
        return false;
    }

    BridgeBeam &beam = beams[best];
    int a = beam.a;
    int b = beam.b;
    spent -= beam.cost;
    DestroyBeamPhysics(beam);
    beam.removed = true;

    // Drop any free node this beam was the last thing holding onto.
    for (int nodeIdx : {a, b})
    {
        BridgeNode &node = nodes[nodeIdx];
        if (node.anchor == AnchorKind::None && node.alive && NodeActiveBeamCount(nodeIdx) == 0)
        {
            PolygonFactory::Destroy(scene, node.polygon);
            node.body = nullptr;
            node.alive = false;
            if (pendingNode == nodeIdx)
                pendingNode = -1;
        }
    }

    message = "Beam removed";
    return true;
}

void BridgeGraph::BreakBeam(int idx)
{
    BridgeBeam &beam = beams[idx];
    if (beam.broken || beam.removed)
        return;

    // Box2D 2.4 has no joint breaking of its own: cut the hinges and leave the
    // beam's body behind as unconstrained debris, still drawn, now red.
    if (beam.jointA)
    {
        scene.world->DestroyJoint(beam.jointA);
        beam.jointA = nullptr;
    }
    if (beam.jointB)
    {
        scene.world->DestroyJoint(beam.jointB);
        beam.jointB = nullptr;
    }
    beam.broken = true;
    beam.stress = 1.f;
}

void BridgeGraph::UpdateStress()
{
    const float invDt = 1.0f / FIXED_DT;
    const float alpha = STRESS_EMA_RATE * FIXED_DT < 1.f ? STRESS_EMA_RATE * FIXED_DT : 1.f;

    for (size_t i = 0; i < beams.size(); i++)
    {
        BridgeBeam &beam = beams[i];
        if (beam.removed || beam.broken)
            continue;
        if (!beam.jointA || !beam.jointB)
            continue;

        float loadA = beam.jointA->GetReactionForce(invDt).Length();
        float loadB = beam.jointB->GetReactionForce(invDt).Length();
        float load = loadA > loadB ? loadA : loadB;
        // Deliberately unclamped: clamping the sample to 1 makes the average
        // converge on 1 from below and, in float, stall an ulp short of it
        // forever - a beam could never actually reach the break threshold.
        // Overload pulls the average past 1 instead, and how far past decides
        // how many steps it survives.
        float sample = load / BEAM_BREAK_FORCE;

        beam.stress += (sample - beam.stress) * alpha;

        if (beam.stress >= 1.f)
            BreakBeam(static_cast<int>(i));
    }
}

void BridgeGraph::Teardown()
{
    for (BridgeBeam &beam : beams)
        DestroyBeamPhysics(beam);

    for (BridgeNode &node : nodes)
    {
        PolygonFactory::Destroy(scene, node.polygon); // no-op for anchored nodes
        node.body = nullptr;
    }
}

void BridgeGraph::Instantiate(Terrain &terrain, Deck &deck)
{
    for (size_t i = 0; i < nodes.size(); i++)
        if (nodes[i].alive)
            InstantiateNode(static_cast<int>(i), terrain, deck);

    for (size_t i = 0; i < beams.size(); i++)
        if (!beams[i].removed)
            InstantiateBeam(static_cast<int>(i));
}

void BridgeGraph::SetFrozen(bool value)
{
    frozen = value;

    for (BridgeNode &node : nodes)
    {
        if (node.polygon)
            PolygonFactory::SetStatic(node.polygon, value);
    }
    for (BridgeBeam &beam : beams)
    {
        if (beam.polygon)
            PolygonFactory::SetStatic(beam.polygon, value);
    }
}

void BridgeGraph::RefreshVisuals(Vector2 cursorPos, bool showPreview)
{
    for (BridgeBeam &beam : beams)
    {
        if (!beam.polygon)
            continue;

        int color = BEAM_OK_COLOR;
        if (beam.broken || beam.stress >= STRESS_CRITICAL)
            color = BEAM_CRITICAL_COLOR;
        else if (beam.stress >= STRESS_WARN)
            color = BEAM_WARN_COLOR;

        if (color != beam.shownColor)
        {
            beam.polygon->SetColor(color);
            beam.shownColor = color;
        }
    }

    previewDrawer->ResetDrawingParticleIndex();
    if (showPreview && HasPending())
        previewDrawer->DrawLine(nodes[pendingNode].position, cursorPos);
}

int BridgeGraph::BeamCount() const
{
    int count = 0;
    for (const BridgeBeam &beam : beams)
        if (!beam.removed)
            count++;
    return count;
}

int BridgeGraph::BrokenCount() const
{
    int count = 0;
    for (const BridgeBeam &beam : beams)
        if (beam.broken)
            count++;
    return count;
}
