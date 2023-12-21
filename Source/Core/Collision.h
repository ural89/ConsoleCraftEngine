#pragma once
#include "../Core.h"
#include "GameObject.h"
#include <vector>
class GE_API Collision
{
public:
    void AddGameObject(GameObject* gameObject);
    void CheckForCollisions();
    ~Collision();


private:
    std::vector< GameObject*> gameObjects;  
};

