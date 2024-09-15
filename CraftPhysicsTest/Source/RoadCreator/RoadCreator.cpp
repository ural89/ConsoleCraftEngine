#include "RoadCreator.h"
#include "Core/Physics/Polygon/PolygonCreator/PolygonCreator.h"
#include "Core/Physics/Polygon/JointCreator.h"
#include "Core/Physics/Polygon/Polygon.h"
#include "Core/Scene.h"
RoadCreator::RoadCreator(Scene &scene, PolygonCreator &polygonCreator) : scene(scene), polygonCreator(polygonCreator)
{
}
void RoadCreator::CreateRoad(int amount, Vector2 startPosition, Vector2 endPosition)
{
    float jointOffset = 2;

    Vector2 stepSize = (endPosition - startPosition) / amount;
    b2Body *previousBody = nullptr;
    b2Body *firstBody = nullptr;

    for (int i = 0; i < amount; ++i)
    {

        Vector2 currentPosition = startPosition + (stepSize * i);
        Polygon *currentPolygon = polygonCreator.CreateRectanglePolygon({currentPosition, Vector2(6, 2), 0});

        b2Body *currentBody = currentPolygon->GetBody();

        if (i == 0 || i == amount - 1)
        {
            firstBody = currentBody;
            currentBody->SetType(b2_staticBody);
        }

        if (previousBody != nullptr)
        {
            b2DistanceJointDef jointDef;
            jointDef.bodyA = previousBody;
            jointDef.bodyB = currentBody;
            jointDef.collideConnected = false;
            jointDef.localAnchorA = previousBody->GetLocalCenter() + b2Vec2(jointOffset, 0);
            jointDef.localAnchorB = currentBody->GetLocalCenter() - b2Vec2(jointOffset, 0);
            jointDef.maxLength = 15;
            jointDef.stiffness = 2325;
            jointDef.length = 2;

            b2Joint *joint = scene.world->CreateJoint(&jointDef);
        }

        previousBody = currentBody;
    }

    if (firstBody != nullptr)
    {
        firstBody->SetType(b2_staticBody);
    }
}
