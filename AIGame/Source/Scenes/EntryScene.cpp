#include "EntryScene.h"
#include "../GameObjects/PlayerShip.h"
#include "../GameObjects/Enemy.h"
#include "Core/AI/Pathfinder.h"

EntryScene::
    ~EntryScene()
{
}
void EntryScene::Init()
{
    Scene::Init();
}

void EntryScene::Start()
{
    Scene::Start();
    playerShip = new PlayerShip(*this);
    enemy = new Enemy(*this);
    AddGameObject(playerShip, Vector2(7, 5));
    AddGameObject(enemy, Vector2(15, 5));
    m_Pathfinder = new Pathfinder(*this);
    m_Linedrawer = new LineDrawer(*this);

    m_Linedrawer->CreateLineParticles(100, 1);
}

void EntryScene::Update(float deltaTime)
{
    Scene::Update(deltaTime);
    m_Linedrawer->ResetDrawingParticleIndex();
    // TODO: AI movement
    PathNode start(0, 0);
    PathNode goal(playerShip->transform.Position.X - 1, playerShip->transform.Position.Y - 1);
    std::vector<PathNode> path = m_Pathfinder->FindPath(start, goal);
    Vector2 enemyMoveDirection = enemy->transform.Position - playerShip->transform.Position;
    if (!path.empty())
    {

        for (int i = 0; i < path.size() - 1; i++)
        {
            Vector2 posStart = Vector2(path[i].x, path[i].y);
            Vector2 posEnd = Vector2(path[i + 1].x, path[i + 1].y);

            m_Linedrawer->DrawLine(posStart, posEnd);
        }
    }
}
