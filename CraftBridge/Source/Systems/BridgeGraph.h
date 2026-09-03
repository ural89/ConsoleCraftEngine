#pragma once
#include "CoreStructs/Vector.h"
#include <string>
#include <vector>

class b2Body;
class b2Joint;
class Polygon;
class Terrain;
class Deck;

enum class AnchorKind
{
    None,
    TerrainLeft,
    TerrainRight,
    Pillar,
    Deck
};

struct BridgeNode
{
    Vector2 position;
    AnchorKind anchor = AnchorKind::None;
    int deckSegmentIndex = -1;
    Polygon *polygon = nullptr; // only free nodes own a shape of their own
    b2Body *body = nullptr;     // the shape's body, or the anchor's, per instantiation
    bool alive = true;          // false once a now-beamless free node has been dropped
};

struct BridgeBeam
{
    int a = -1;
    int b = -1;
    float cost = 0.f;
    Polygon *polygon = nullptr;
    b2Joint *jointA = nullptr;
    b2Joint *jointB = nullptr;
    bool broken = false;  // snapped under load during Test; the shape stays as debris
    bool removed = false; // deleted by the player; nothing left to draw
    float stress = 0.f;   // smoothed 0..1, drives the beam's colour
    int shownColor = 0;   // last colour pushed to the polygon, so we only recolour on a change
};

// The player's design: nodes + beams, kept independent of their live polygons
// and joints so a retry (R) can tear the physics down and rebuild the exact
// same structure. See CraftBridge.md "BridgeGraph" for the full rationale.
class BridgeGraph
{
public:
    BridgeGraph(class Scene &scene, class PolygonCreator &polygonCreator, class JointCreator &jointCreator);
    ~BridgeGraph();

    void Reset(float budget);

    // Build-phase interaction. `terrain`/`deck` are consulted for anchor snapping.
    int FindOrCreateNode(Vector2 pos, Terrain &terrain, Deck &deck);
    bool AddBeam(int a, int b, std::string &message);
    bool RemoveNearestBeam(Vector2 pos, std::string &message);

    void SetPending(int idx) { pendingNode = idx; }
    void ClearPending() { pendingNode = -1; }
    bool HasPending() const { return pendingNode >= 0; }
    int PendingNode() const { return pendingNode; }
    Vector2 NodePosition(int idx) const { return nodes[idx].position; }

    void Teardown();                                // destroy every owned shape/joint; keeps the model
    void Instantiate(Terrain &terrain, Deck &deck); // rebuild shapes/joints from the model
    void Rebuild(Terrain &terrain, Deck &deck)
    {
        Teardown();
        Instantiate(terrain, deck);
    }

    void SetFrozen(bool frozen);
    void UpdateStress(); // call once per fixed physics step during Test

    // Polygons draw themselves, so all this does is push stress colours and
    // redraw the rubber-band line to a half-placed beam's second point.
    void RefreshVisuals(Vector2 cursorPos, bool showPreview);

    float Budget() const { return budget; }
    float Spent() const { return spent; }
    int BeamCount() const;
    int BrokenCount() const;

private:
    Scene &scene;
    PolygonCreator &polygonCreator;
    JointCreator &jointCreator;
    class LineDrawer *previewDrawer;

    std::vector<BridgeNode> nodes;
    std::vector<BridgeBeam> beams;
    int pendingNode = -1;
    float budget = 0.f;
    float spent = 0.f;
    bool frozen = true;

    void InstantiateNode(int idx, Terrain &terrain, Deck &deck);
    void InstantiateBeam(int idx);
    void DestroyBeamPhysics(BridgeBeam &beam);
    void BreakBeam(int idx);
    b2Body *ResolveAnchorBody(const BridgeNode &node, Terrain &terrain, Deck &deck) const;
    int FindNearestNode(Vector2 pos) const;
    int FindNearestDeckSegment(Vector2 pos, Deck &deck) const;
    int NodeActiveBeamCount(int nodeIdx) const;
};
