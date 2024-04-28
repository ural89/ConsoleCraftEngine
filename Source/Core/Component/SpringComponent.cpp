#include "SpringComponent.h"

SpringComponent::~SpringComponent()
{
}

void SpringComponent::Init()
{
    torq = 50;
}

void SpringComponent::Update(float deltaTime)
{
    if (firstAttachment != nullptr && secondAttachment != nullptr)
    {
        Vector2 force = firstAttachment->GetCenterPosition() - secondAttachment->GetCenterPosition(); //TODO: this causes starting bug
        force = (force - startOffset) * stiffness;
        secondAttachment->AddForce(force / 2);
        firstAttachment->AddForce((force * -1) / 2);

        UpdateRotation(deltaTime);
    }
}

void SpringComponent::AddTorque(float _torque)
{
 //   if (this != nullptr)
        this->torq += _torque;
}

void SpringComponent::UpdateRotation(float deltaTime)
{
    angularVelocity += torq * deltaTime;
    angularVelocity *= (1 - 0.6 * deltaTime) ;
    float springAngle = angularVelocity * (3.14159f / 180.0f) * deltaTime;
   // std::cout<< angularVelocity << '\n';
    float newX = std::cos(springAngle) * startOffset.X - std::sin(springAngle) * startOffset.Y;
    float newY = std::sin(springAngle) * startOffset.X + std::cos(springAngle) * startOffset.Y;
    startOffset.X = newX;
    startOffset.Y = newY;
    torq = 0;
}
