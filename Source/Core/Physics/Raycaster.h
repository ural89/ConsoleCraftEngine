#pragma once
#include "../../CoreStructs/Vector.h"
struct RayHit
{
public:
    class GameObject* gameObject;
};

class Raycaster
{
public:
    Raycaster(class Scene& scene) : scene(scene)
    {

    }

    bool RayCast(Vector2 startPosition, Vector2 direction, RayHit& rayHit, int distance);
private:
    Scene& scene;
};