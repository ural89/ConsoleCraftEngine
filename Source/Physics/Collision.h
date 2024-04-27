#pragma once

#include "Core/Typedefs.h"

#include "Core/GameObject.h"


class GE_API Collision
{
public:
    void AddGameObject(GameObject* gameObject);
    void RemoveGameObject(GameObject* gameObject);
    void CheckForCollisions() const;
    void CheckForBorderCollisions() const;
    ~Collision();


private:
    std::vector< GameObject*> gameObjects;  
};

