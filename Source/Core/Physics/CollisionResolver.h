#pragma once
#include "../../Core.h"
#include "../Component/RigidbodyComponent.h"
#include <vector>
#include "../../CoreStructs/Vector.h"
#include "../UIHandler.h"

class GE_API CollisionResolver
{
public:
    CollisionResolver(class Scene &scene);
    ~CollisionResolver()
    {
        rigidbodies.clear();
    }
    void AddRigidbody(Rigidbody *rb);
    void RemoveRigidbody(Rigidbody *rb);
    void UpdateResolve(float deltaTime);
    bool HasOverlapped(Rigidbody *&first, Rigidbody *&second);
    void UpdateBorderResolve(float deltaTime);
    void SeparateObjects(Rigidbody *first, Rigidbody *second, float deltaTime);

private:
    void ResolveCollision(Rigidbody *first, Rigidbody *second, float deltaTime);

    Vector2 Velocity;
    float Restitution; // Coefficient of restitution (elasticity)
    
    std::shared_ptr<UIData> debugUIPtr;
    UIData debugUI;

    std::vector<Rigidbody *> rigidbodies;
};