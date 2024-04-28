#include "CollisionResolver.h"
#include "../Scene.h"

Vector2 operator/(float scalar, const Vector2 &vector)
{
    if (vector.X != 0 && vector.Y != 0)
    {
        return Vector2(scalar / vector.X, scalar / vector.Y);
    }
    else
    {
        // Handle division by zero (return a zero vector in this case)
        return Vector2(0.0f, 0.0f);
    }
}
CollisionResolver::CollisionResolver(Scene &scene)
{

    debugUI.position = Vector2(0, 27);
    debugUIPtr = std::make_shared<UIData>(debugUI);
    scene.uiHandler->AddString(debugUIPtr);
}
void CollisionResolver::AddRigidbody(Rigidbody *rb)
{
    rigidbodies.push_back(rb);
}

void CollisionResolver::RemoveRigidbody(Rigidbody *rb)
{
    rigidbodies.erase(std::remove(rigidbodies.begin(), rigidbodies.end(), rb), rigidbodies.end());
}

void CollisionResolver::UpdateResolve(float deltaTime) //Not in use. Polygon collision resolver instead
{
    for (size_t i = 0; i < rigidbodies.size(); ++i)
    {
        for (size_t j = i + 1; j < rigidbodies.size(); ++j)
        {

            if (rigidbodies[i]->canCollide || rigidbodies[j]->canCollide)
            {
                auto &first = rigidbodies[i];
                auto &second = rigidbodies[j];
                if (first->GetTransform().HasMovedThisFrame || second->GetTransform().HasMovedThisFrame)
                {
                    if (HasOverlapped(first, second))
                    {
                        ResolveCollision(first, second, deltaTime);
                    }
                }
            }
        }
    }
}
void CollisionResolver::ResolveCollision(Rigidbody *first, Rigidbody *second, float deltaTime)
{

    Vector2 relativeVelocity = second->velocity - first->velocity;

    Vector2 normal = (second->GetCenterPosition() - first->GetCenterPosition());
    normal.Normalize();

    float impulse = (2.0f * relativeVelocity.Dot(normal)) / (first->GetMass() + second->GetMass());

    first->velocity += normal * impulse / first->GetMass();
    second->velocity -= normal * impulse / second->GetMass();
    // debugUIPtr->text = "first: " + first->velocity.to_string() + " second: " + second->velocity.to_string() + '\n' + "normal: " + normal.to_string();
    // SeparateObjects(first, second, deltaTime);
}
void CollisionResolver::SeparateObjects(Rigidbody *first, Rigidbody *second, float deltaTime)
{

    Vector2 separationVector = second->GetCenterPosition() - first->GetCenterPosition();
    float overlap = (first->GetWidth() + second->GetWidth()) / 2 - std::abs(separationVector.X);
    overlap = std::max(overlap, 0.0f);

    Vector2 separationDirection = separationVector;
    separationDirection.Normalize();

    Vector2 separationOffset = separationDirection * overlap / 2.0f;
    debugUIPtr->text = separationOffset.to_string();
    float seperationForce = 20;
    first->AddForce(Vector2(-separationOffset.X, -separationOffset.Y) * deltaTime * seperationForce);
    second->AddForce(Vector2(separationOffset.X, separationOffset.Y) * deltaTime * seperationForce);
}
bool CollisionResolver::HasOverlapped(Rigidbody *&first, Rigidbody *&second)
{
    return first->GetTransform().Position.X <= second->GetTransform().Position.X + second->GetWidth() &&
           second->GetTransform().Position.X <= first->GetTransform().Position.X + first->GetWidth() &&
           first->GetTransform().Position.Y <= second->GetTransform().Position.Y + second->GetHeight() &&
           second->GetTransform().Position.Y <= first->GetTransform().Position.Y + first->GetHeight();
}

void CollisionResolver::UpdateBorderResolve(float deltaTime)
{
    for (auto &rb : rigidbodies)
    {
        if (!rb->canCollideBorder)
            return;
        if (rb->GetTransform().Position.X + 1 >= SCREENWIDTH)
            rb->OnCollidedBorder(RIGHTBORDER);
        if (rb->GetTransform().Position.X - 1 <= 0)
            rb->OnCollidedBorder(LEFTBORDER);
        if (rb->GetTransform().Position.Y + 1 >= SCREENHEIGHT)
            rb->OnCollidedBorder(BOTTOMBORDER);
        if (rb->GetTransform().Position.Y - 1 <= 0)
            rb->OnCollidedBorder(TOPBORDER);
    }
}
