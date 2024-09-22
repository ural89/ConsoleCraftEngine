#include "EntryScene.h"
#include "../GameObjects/PlayerShip.h"
#include "Core/LineDrawer.h"
#include "Core/AI/Pathfinder.h"

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
    Pathfinder pathfinder;
    // Define a simple grid (0 = walkable, 1 = obstacle)
    std::vector<std::vector<int>> graph = {
        {0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 1, 1, 1},
        {0, 0, 0, 1, 0, 1, 1, 1},
        {1, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 1, 1, 1},
        {0, 0, 0, 1, 0, 0, 1, 1},
        {0, 0, 0, 1, 0, 0, 0, 1},
        {0, 0, 0, 1, 0, 1, 0, 0},

    };

    PathNode start(0, 0);
    PathNode goal(7, 7);

    std::vector<PathNode> path = pathfinder.FindPath(graph, start, goal);

    LineDrawer lineDrawer(*this);
    lineDrawer.ResetDrawingParticleIndex();
    lineDrawer.CreateLineParticles(30, 1);
    if (!path.empty())
    for (int i = 0; i < path.size() - 1; i++)
    {
        Vector2 posStart = Vector2(path[i].x, path[i].y);
        Vector2 posEnd = Vector2(path[i + 1].x, path[i + 1].y);

        lineDrawer.DrawLine(posStart, posEnd);
    }
}

void EntryScene::Update(float deltaTime)
{
    Scene::Update(deltaTime);
}
