#pragma once

#include "../../../Core.h"
#include "../../../CoreStructs/Vector.h"
#include "PolygonCreator/PolygonCursor.h"
class b2Body;
class b2Joint;
class Scene;

class GE_API JointCreator
{
public:
    JointCreator(Scene &scene);
    ~JointCreator()
    {
      
    }
    void SetBody(b2Body *body);

    // Gates the interactive 'j' pick tool and its cursor. Active by default.
    void SetEditingActive(bool isActive);

    // Pin two bodies together at a world point - a hinge. Returns the joint so
    // callers can read GetReactionForce off it or destroy it on their own terms.
    b2Joint *CreateRevoluteJoint(b2Body *bodyA, b2Body *bodyB, Vector2 worldAnchor, bool collideConnected = false);

    // The same hinge, driven by a motor (wheels, winches).
    b2Joint *CreateMotorJoint(b2Body *bodyA, b2Body *bodyB, Vector2 worldAnchor, float maxMotorTorque, float motorSpeed);

private:
    b2Body *firstBody;
    Scene &scene;
    b2Body *secondBody;
    class Cursor* cursor;
    bool isEditingActive = true;

private:
    void OnInput(int input);
    void SetFirstBody(b2Body *firstBody);
    void SetSecondBody(b2Body *secondBody);
    void CreateDistanceJoint();
};
