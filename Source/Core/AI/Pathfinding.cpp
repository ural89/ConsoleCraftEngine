#include "Pathfinding.h"
#include "../Scene.h"
Pathfinding::Pathfinding(Scene &scene) : m_Scene(scene)
{
}

void Pathfinding::ShowGameObjects()
{
    auto &gameObjects = m_Scene.GetGameObjects();
    for (auto &gameObject : gameObjects)
    {
        std::cout << gameObject->name << '\n';
    }
}
