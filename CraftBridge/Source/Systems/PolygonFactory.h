#pragma once
#include "CoreStructs/Vector.h"

class Polygon;
class PolygonCreator;
class Scene;

// Everything physical in this game is an engine Polygon built through
// PolygonCreator, exactly as CraftPhysicsTest does it. PolygonCreator always
// hands back a *dynamic* body with density 1 / friction 0.9 / restitution 0.2
// and a visible 'X' GameObject at every corner, so these helpers cover the
// fix-ups every caller here needs right after a shape is created.
namespace PolygonFactory
{
    // A box centred on `center`. PolygonCreator::CreateRectanglePolygon takes
    // the box's *corner* and rotates the shape about that corner, which is
    // never what a beam/plank/chassis wants.
    Polygon *CreateBox(PolygonCreator &creator, Vector2 center, Vector2 size, float rotationDegrees, int color, int maxParticlesToDraw);

    // Rewrites the single fixture Polygon::Init() created.
    void SetPhysics(Polygon *polygon, float density, float friction, short groupIndex,
                    unsigned short categoryBits, unsigned short maskBits);
    void SetStatic(Polygon *polygon, bool isStatic);

    // Call once on every created polygon. Corner markers are the only visible
    // part of a shape whose edges are under a console cell (nodes, wheels) and
    // pure noise on anything bigger. Either way the corners drop out of the
    // scene's O(n^2) trigger-collision and name-lookup passes: a bridge is
    // hundreds of these, and nothing here uses GameObject-level collision.
    void PrepareCorners(Polygon *polygon, bool visible);

    // Destroys the body, its joints, the corner particles and the outline.
    void Destroy(Scene &scene, Polygon *&polygon);
}
