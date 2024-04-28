#include "Raycaster.h"
#include "../Collision.h"
#include "../Scene.h"
#include "../GameObject.h"

bool Raycaster::RayCast(Vector2 startPosition, Vector2 direction, RayHit &rayHit, int distance)
{
    int dist = 0;
    bool hasHit = false;
   while (!hasHit && dist <= distance)
    {
        auto hit = scene.collision.GetCollidedObject(startPosition + direction * dist); 
        if (hit != nullptr && (hit->name == "Brick"))// || hit->name == "Bomber"))
        {
            hasHit = true;
            rayHit.gameObject = hit; 
            return true;
        }
        dist++;
    }
    return false;
}

