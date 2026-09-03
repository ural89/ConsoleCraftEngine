#pragma once
#include "CoreStructs/Vector.h"

class Polygon;

// A small motorised car: a chassis outline on two motor-driven hexagon wheels.
// This is CraftPhysicsTest's Car.cpp recipe - PolygonCreator for the shapes,
// motorised revolute joints for the wheels - scaled down to bridge size and
// wrapped in Spawn/Despawn so every Test attempt starts from a clean rig.
class Vehicle
{
public:
    Vehicle(class Scene &scene, class PolygonCreator &polygonCreator, class JointCreator &jointCreator);
    ~Vehicle();

    // `x` = spawn center X. `surfaceY` = the world Y of the surface the
    // wheels should rest on (deck/plateau top).
    void Spawn(float x, float surfaceY);
    void Despawn();
    bool IsSpawned() const { return chassis != nullptr; }

    Vector2 ChassisPosition() const;
    float ChassisAngleDegrees() const;

private:
    Scene &scene;
    PolygonCreator &polygonCreator;
    JointCreator &jointCreator;

    Polygon *chassis = nullptr;
    Polygon *wheelLeft = nullptr;
    Polygon *wheelRight = nullptr;

    Polygon *MakeWheel(Vector2 center);
};
