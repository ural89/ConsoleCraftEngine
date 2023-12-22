#pragma once
#include "../Core.h"
#include "GameObject.h"
#include <vector>
class GE_API Collision
{
public:
    void AddGameObject(GameObject* gameObject);
    void RemoveGameObject(GameObject* gameObject);
    void CheckForCollisions() const;
    ~Collision();


private:
    std::vector< GameObject*> gameObjects;  
};

