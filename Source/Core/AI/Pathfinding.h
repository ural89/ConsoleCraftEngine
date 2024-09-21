#pragma once

class Pathfinding
{
public:
    Pathfinding(class Scene &scene);
    void ShowGameObjects();
private:
    Scene& m_Scene;
};