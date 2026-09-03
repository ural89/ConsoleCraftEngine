#include "Terrain.h"
#include "PolygonFactory.h"
#include "../BridgeConfig.h"
#include "Core/Physics/Polygon/Polygon.h"
#include "Core/Physics/Polygon/PolygonCreator/PolygonCreator.h"
#include "Core/Scene.h"

const float PILLAR_HALF_WIDTH = 1.6f;

Terrain::Terrain(Scene &scene, PolygonCreator &polygonCreator) : scene(scene), polygonCreator(polygonCreator)
{
}

Terrain::~Terrain()
{
    Teardown();
}

Polygon *Terrain::MakeBox(Vector2 center, Vector2 size)
{
    Polygon *polygon = PolygonFactory::CreateBox(polygonCreator, center, size, 0.f, TERRAIN_COLOR, TERRAIN_GLYPHS);
    PolygonFactory::SetPhysics(polygon, 0.f, 0.8f, 0, CATEGORY_TERRAIN, MASK_ALL);
    PolygonFactory::SetStatic(polygon, true);
    PolygonFactory::PrepareCorners(polygon, false);
    return polygon;
}

void Terrain::Build(const LevelData &newLevel)
{
    Teardown();
    level = newLevel;

    float bottom = static_cast<float>(SCREENHEIGHT);
    float screenW = static_cast<float>(SCREENWIDTH);

    Vector2 leftCenter(level.leftCliffX * 0.5f, (level.groundY + bottom) * 0.5f);
    Vector2 leftSize(level.leftCliffX, bottom - level.groundY);
    leftPolygon = MakeBox(leftCenter, leftSize);

    Vector2 rightCenter((level.rightCliffX + screenW) * 0.5f, (level.groundY + bottom) * 0.5f);
    Vector2 rightSize(screenW - level.rightCliffX, bottom - level.groundY);
    rightPolygon = MakeBox(rightCenter, rightSize);

    if (level.hasPillar)
    {
        Vector2 pillarCenter(level.pillarX, (level.pillarTopY + bottom) * 0.5f);
        Vector2 pillarSize(PILLAR_HALF_WIDTH * 2.f, bottom - level.pillarTopY);
        pillarPolygon = MakeBox(pillarCenter, pillarSize);
    }
}

void Terrain::Teardown()
{
    // Destroying a body destroys every joint on it, so the deck's end hinges
    // and any beam pinned to a cliff go with these - which is why callers tear
    // the graph and the deck down first and never keep joint pointers around.
    PolygonFactory::Destroy(scene, leftPolygon);
    PolygonFactory::Destroy(scene, rightPolygon);
    PolygonFactory::Destroy(scene, pillarPolygon);
}

b2Body *Terrain::LeftBody() const
{
    return leftPolygon ? leftPolygon->GetBody() : nullptr;
}

b2Body *Terrain::RightBody() const
{
    return rightPolygon ? rightPolygon->GetBody() : nullptr;
}

b2Body *Terrain::PillarBody() const
{
    return pillarPolygon ? pillarPolygon->GetBody() : nullptr;
}

static bool NearTopEdge(Vector2 p, float x0, float x1, float y, float radius)
{
    float clampedX = p.X;
    if (clampedX < x0)
        clampedX = x0;
    if (clampedX > x1)
        clampedX = x1;
    Vector2 nearest(clampedX, y);
    return Vector2::Distance(p, nearest) <= radius;
}

bool Terrain::NearLeft(Vector2 p) const
{
    return NearTopEdge(p, 0.f, level.leftCliffX, level.groundY, NODE_SNAP_RADIUS);
}

bool Terrain::NearRight(Vector2 p) const
{
    return NearTopEdge(p, level.rightCliffX, static_cast<float>(SCREENWIDTH), level.groundY, NODE_SNAP_RADIUS);
}

bool Terrain::NearPillar(Vector2 p) const
{
    if (!level.hasPillar)
        return false;
    return NearTopEdge(p, level.pillarX - PILLAR_HALF_WIDTH, level.pillarX + PILLAR_HALF_WIDTH, level.pillarTopY, NODE_SNAP_RADIUS);
}
