#pragma once
#include "Component.h"
#include "../GameObject.h"
#include "../Component/RigidbodyComponent.h"
#include "../../CoreStructs/Vector.h"
class GE_API SpringComponent : public Component
{
public:
    SpringComponent(GameObject &owner, float stiffness) : Component(owner), stiffness(stiffness)
    {
    }
    ~SpringComponent();
    void Init() override;
    void Update(float deltaTime) override;
    void SetAttachments(Rigidbody *first, Rigidbody *second)
    {
        firstAttachment = first;
        secondAttachment = second;
        startOffset = first->GetCenterPosition() - second->GetCenterPosition();
    }

    float stiffness = 400;
    float torq = 0;
    void AddTorque(float _torque);
  
private:

    void UpdateRotation(float deltaTime);

    Rigidbody *firstAttachment = nullptr;
    Rigidbody *secondAttachment = nullptr;

    float angularVelocity = 0;
    float angularDrag = 0.5f;

    Vector2 startOffset;
};