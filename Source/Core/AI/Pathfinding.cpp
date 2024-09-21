#include "Pathfinding.h"
#include "../Scene.h"
Pathfinding::Pathfinding(Scene &scene)
{
    auto& gameObjects = scene.GetGameObjects();
    for (auto&  gameObject : gameObjects)
    {
        std::cout << gameObject->name << '\n';
    }
    
}