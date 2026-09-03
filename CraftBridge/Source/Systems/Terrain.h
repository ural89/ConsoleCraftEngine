#pragma once
#include "CoreStructs/Vector.h"
#include "../Levels/LevelData.h"

class b2Body;
class Polygon;

// The two static cliffs (and, on some levels, a mid-gap pillar) that anchor
// the deck and the player's supports. Each one is a PolygonCreator rectangle
// flipped to a static body, the same recipe RoadCreator uses for the ends of
// its road. Rebuilt fresh every level/retry.
class Terrain
{
public:
    Terrain(class Scene &scene, class PolygonCreator &polygonCreator);
    ~Terrain();

    void Build(const LevelData &level);
    void Teardown();

    b2Body *LeftBody() const;
    b2Body *RightBody() const;
    b2Body *PillarBody() const; // nullptr if this level has none

    // True when `p` is close enough to this surface's top edge to anchor a node to it.
    bool NearLeft(Vector2 p) const;
    bool NearRight(Vector2 p) const;
    bool NearPillar(Vector2 p) const;

    float GroundY() const { return level.groundY; }

private:
    Scene &scene;
    PolygonCreator &polygonCreator;
    LevelData level;

    Polygon *leftPolygon = nullptr;
    Polygon *rightPolygon = nullptr;
    Polygon *pillarPolygon = nullptr;

    Polygon *MakeBox(Vector2 center, Vector2 size);
};
