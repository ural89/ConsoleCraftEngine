#pragma once
#include "../Core.h"
#include "GameObject.h"
#include <vector>
#include <set>
// this for trigger collisions
class GE_API Collision
{
public:
    void AddGameObject(GameObject *gameObject);
    void RemoveGameObject(GameObject *gameObject);
    void CheckForCollisions();
    void CheckForBorderCollisions() const;
    GameObject* GetCollidedObject(Vector2 position);
    ~Collision();

private:
    std::set<std::pair<GameObject *, GameObject *>> collidingPairs;
    std::vector<GameObject *> gameObjects;
};
