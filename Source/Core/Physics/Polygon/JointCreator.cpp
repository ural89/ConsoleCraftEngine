#include "JointCreator.h"
#include "../../Scene.h"
#include "../../../box2d/include/box2d/b2_joint.h"
#include "../../../box2d/include/box2d/b2_body.h"
#include "../../Input.h"
JointCreator::JointCreator(Scene &scene) : scene(scene), firstBody(nullptr), secondBody(nullptr)
{
    auto inputEvent = BIND_EVENT_FN(JointCreator::OnInput);
    Input::AddListener(inputEvent);
    cursor = new Cursor(scene);
    scene.AddGameObject(cursor, Vector2(15, 15));
   
}

void JointCreator::SetBody(b2Body *body)
{
    if (firstBody == nullptr)
        SetFirstBody(body);
    else if (secondBody == nullptr)
        SetSecondBody(body);
    if (firstBody != nullptr && secondBody != nullptr)
    {
        CreateDistanceJoint();
    }
}

void JointCreator::OnInput(int input)
{
    if ('j' == std::tolower(input))
    {
        Vector2 cursorPosition = cursor->transform.Position;
        b2Vec2 worldCursorPos(cursorPosition.X, cursorPosition.Y);
        int i = 0;

        for (b2Body *body = scene.world->GetBodyList(); body; body = body->GetNext())
        {
            if (body->GetFixtureList() && body->GetFixtureList()->TestPoint(worldCursorPos))
            {
                SetBody(body);
                break;
            }
            i++;
        }
    }
}

void JointCreator::SetFirstBody(b2Body *firstBody)
{
    this->firstBody = firstBody;
    std::cout << " first body Set!!\n";
}

void JointCreator::SetSecondBody(b2Body *secondBody)
{
    if (firstBody == secondBody)
    {
        secondBody = nullptr;
        return;
    }
    this->secondBody = secondBody;
    std::cout << " second body Set!!\n";
}

void JointCreator::CreateDistanceJoint()
{
    // Create spring-like joint
    b2DistanceJointDef jd;
    jd.Initialize(firstBody,
                  secondBody,
                  firstBody->GetWorldCenter(), // TODO: local offset
                  secondBody->GetWorldCenter());

    float springFrequencyHz = 5.0f;
    float dampingRatio = 0.7f;

    float angularFrequency = 2.0f * b2_pi * springFrequencyHz;
    jd.stiffness = 20.6;
    jd.length = 3;
    jd.damping = .3f;
    jd.minLength = 2.f;
    jd.maxLength = 50.f;

    jd.collideConnected = true;

    b2Joint *joint = scene.world->CreateJoint(&jd);
    std::cout << "Created joint!!\n";
    // firstBody->ApplyLinearImpulseToCenter(b2Vec2(500, 0), true);
    firstBody = nullptr;
    secondBody = nullptr;
}

void JointCreator::CreateRevoluteJoint()
{
    b2RevoluteJointDef revoluteJointDef;
    revoluteJointDef.bodyA = firstBody;
    revoluteJointDef.bodyB = secondBody;
    revoluteJointDef.collideConnected = false;

    // revoluteJointDef.localAnchorA
}
