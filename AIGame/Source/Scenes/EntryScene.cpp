#include "EntryScene.h"
#include "../GameObjects/PlayerShip.h"
#include "Core/LineDrawer.h"

EntryScene::
    ~EntryScene()
{
}
void EntryScene::Init()
{
    Scene::Init();
    AddGameObject(new PlayerShip(*this), Vector2(5, 5));
}

void EntryScene::Start()
{
    Scene::Start();
    PathNode startNode;
    PathNode targetNode;
    startNode.Position = Vector2(0, 0);
    targetNode.Position = Vector2(2, 2);
    auto path = m_Pathfinding->GetPath(startNode, targetNode);
    std::cout << path.size() << '\n';
    LineDrawer lineDrawer(*this);
    lineDrawer.CreateLineParticles(30, 1);
    lineDrawer.ResetDrawingParticleIndex();
    for (int i = 0; i < path.size() - 1; i++)
    {
        lineDrawer.DrawLine(path[i].Position, path[i + 1].Position);
    }
}

void EntryScene::Update(float deltaTime)
{
    Scene::Update(deltaTime);
}
