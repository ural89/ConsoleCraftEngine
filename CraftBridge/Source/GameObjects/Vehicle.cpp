#include "Vehicle.h"
#include "../Systems/PolygonFactory.h"
#include "../BridgeConfig.h"
#include "Core/Physics/Polygon/Polygon.h"
#include "Core/Physics/Polygon/PolygonCreator/PolygonCreator.h"
#include "Core/Physics/Polygon/JointCreator.h"
#include "Core/Scene.h"

const int WHEEL_SEGMENTS = 6;

Vehicle::Vehicle(Scene &scene, PolygonCreator &polygonCreator, JointCreator &jointCreator)
    : scene(scene), polygonCreator(polygonCreator), jointCreator(jointCreator)
{
}

Vehicle::~Vehicle()
{
    Despawn();
}

Polygon *Vehicle::MakeWheel(Vector2 center)
{
    Polygon *wheel = polygonCreator.CreateCircle(center, VEHICLE_WHEEL_RADIUS, WHEEL_SEGMENTS, VEHICLE_COLOR, WHEEL_GLYPHS);
    PolygonFactory::SetPhysics(wheel, VEHICLE_DENSITY, 1.7f, VEHICLE_GROUP);
    // A wheel is barely wider than a console cell, so the rim never draws a
    // full run of line glyphs; its corner markers are what you actually see
    // turning over.
    PolygonFactory::PrepareCorners(wheel, true);
    return wheel;
}

void Vehicle::Spawn(float x, float surfaceY)
{
    Despawn();

    float wheelOffsetX = VEHICLE_CHASSIS_HALF_W * 0.6f;
    float wheelCenterY = surfaceY - VEHICLE_WHEEL_RADIUS - 0.05f;
    float chassisCenterY = wheelCenterY - VEHICLE_CHASSIS_HALF_H - VEHICLE_WHEEL_RADIUS * 0.4f;

    // Drawn point by point through PolygonCreator (Car.cpp's StartCreating /
    // SetPosition / ApplyAndGetPolygon flow) to get a car silhouette with a
    // sloped nose rather than a plain box. Y grows downwards.
    Vector2 nose(x + VEHICLE_CHASSIS_HALF_W, chassisCenterY);
    polygonCreator.StartCreating(Vector2(x - VEHICLE_CHASSIS_HALF_W, chassisCenterY - VEHICLE_CHASSIS_HALF_H), VEHICLE_COLOR, CHASSIS_GLYPHS);
    polygonCreator.SetPosition(Vector2(x + VEHICLE_CHASSIS_HALF_W * 0.2f, chassisCenterY - VEHICLE_CHASSIS_HALF_H));
    polygonCreator.SetPosition(nose);
    polygonCreator.SetPosition(Vector2(x + VEHICLE_CHASSIS_HALF_W, chassisCenterY + VEHICLE_CHASSIS_HALF_H));
    polygonCreator.SetPosition(Vector2(x - VEHICLE_CHASSIS_HALF_W, chassisCenterY + VEHICLE_CHASSIS_HALF_H));
    chassis = polygonCreator.ApplyAndGetPolygon();

    PolygonFactory::SetPhysics(chassis, VEHICLE_DENSITY, 0.3f, VEHICLE_GROUP);
    PolygonFactory::PrepareCorners(chassis, false);

    wheelLeft = MakeWheel(Vector2(x - wheelOffsetX, wheelCenterY));
    wheelRight = MakeWheel(Vector2(x + wheelOffsetX, wheelCenterY));

    jointCreator.CreateMotorJoint(chassis->GetBody(), wheelLeft->GetBody(), Vector2(x - wheelOffsetX, wheelCenterY),
                                  VEHICLE_MAX_MOTOR_TORQUE, VEHICLE_MOTOR_SPEED);
    jointCreator.CreateMotorJoint(chassis->GetBody(), wheelRight->GetBody(), Vector2(x + wheelOffsetX, wheelCenterY),
                                  VEHICLE_MAX_MOTOR_TORQUE, VEHICLE_MOTOR_SPEED);
}

void Vehicle::Despawn()
{
    // Both motor joints hang off the chassis body and die with it.
    PolygonFactory::Destroy(scene, wheelLeft);
    PolygonFactory::Destroy(scene, wheelRight);
    PolygonFactory::Destroy(scene, chassis);
}

Vector2 Vehicle::ChassisPosition() const
{
    if (!chassis || !chassis->GetBody())
        return Vector2(0.f, 0.f);
    b2Vec2 p = chassis->GetBody()->GetPosition();
    return Vector2(p.x, p.y);
}

float Vehicle::ChassisAngleDegrees() const
{
    if (!chassis || !chassis->GetBody())
        return 0.f;
    return chassis->GetBody()->GetAngle() * (180.0f / 3.14159265f);
}
