#include "Car.h"
#include "CoreStructs/Vector.h"
#include "Core/Physics/Polygon/PolygonCreator/PolygonCreator.h"
#include "Core/Scene.h"
Car::Car(Scene& scene, PolygonCreator &polygonCreator) : polygonCreator(polygonCreator), scene(scene)
{
}

void Car::Init(Vector2 position)
{
    //Create car body
    polygonCreator.StartCreating(position, 3);
    polygonCreator.SetPosition(position + Vector2(3, 0));
    polygonCreator.SetPosition(position + Vector2(7, -3));
    polygonCreator.SetPosition(position + Vector2(10, -3));
    polygonCreator.SetPosition(position + Vector2(12, 0));
    polygonCreator.SetPosition(position + Vector2(18, 0));
    polygonCreator.SetPosition(position + Vector2(18, 2));
    polygonCreator.SetPosition(position + Vector2(0, 2));
    auto carBodyPolygon = polygonCreator.ApplyAndGetPolygon();
    
    int tyreSize = 3;
    int tyreSegment = 6;
    //Create left tyre
    auto tyreLeft = polygonCreator.CreateCircle(Vector2(position), tyreSize, tyreSegment, 2);
    b2RevoluteJointDef leftRevololuteJointDef;
    leftRevololuteJointDef.bodyA = carBodyPolygon->GetBody();
    leftRevololuteJointDef.bodyB = tyreLeft->GetBody();
    leftRevololuteJointDef.collideConnected = false;
    leftRevololuteJointDef.localAnchorA.Set(5, 2);
        //Set motor
    leftRevololuteJointDef.enableMotor = true;
    leftRevololuteJointDef.maxMotorTorque = 1000;
    leftRevololuteJointDef.motorSpeed = 3.14 * 4;

    scene.World->CreateJoint(&leftRevololuteJointDef);


    //Create right tyre
    auto tyreRight = polygonCreator.CreateCircle(Vector2(position), tyreSize, tyreSegment, 2);
    b2RevoluteJointDef rightRevololuteJointDef;
    rightRevololuteJointDef.bodyA = carBodyPolygon->GetBody();
    rightRevololuteJointDef.bodyB = tyreRight->GetBody();
    rightRevololuteJointDef.collideConnected = false;
    rightRevololuteJointDef.localAnchorA.Set(-5, 2);

    //Set motor
    rightRevololuteJointDef.enableMotor = true;
    rightRevololuteJointDef.maxMotorTorque = 1000;
    rightRevololuteJointDef.motorSpeed = 3.14 * 4;


    scene.World->CreateJoint(&rightRevololuteJointDef);
    
}

Car::~Car()
{
}
