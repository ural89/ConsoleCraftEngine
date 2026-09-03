#pragma once
#include "CoreStructs/Vector.h"
#include "../Levels/LevelData.h"
#include <vector>

class b2Body;
class Polygon;

// A hinged chain of plank polygons spanning the gap, pinned to each other and
// to the terrain with JointCreator revolute joints. This is RoadCreator's road
// with real hinges at the ends instead of SetType(b2_staticBody), so the deck
// actually hangs and sags when it is not supported from below.
class Deck
{
public:
    Deck(class Scene &scene, class PolygonCreator &polygonCreator, class JointCreator &jointCreator);
    ~Deck();

    void Build(const LevelData &level, class Terrain &terrain);
    void Teardown();

    // Freeze (Build phase) / release (Test phase) every plank body.
    void SetFrozen(bool frozen);

    int SegmentCount() const { return static_cast<int>(segments.size()); }
    b2Body *SegmentBody(int index) const;
    Vector2 SegmentPosition(int index) const;

private:
    Scene &scene;
    PolygonCreator &polygonCreator;
    JointCreator &jointCreator;
    std::vector<Polygon *> segments;
};
