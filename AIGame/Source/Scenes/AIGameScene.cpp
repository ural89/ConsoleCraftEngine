#include "AIGameScene.h"
#include "../GameObjects/PlayerShip.h"
#include "../GameObjects/Enemy.h"
#include "../GameObjects/Brick.h"

#include "Core/Component/AI/Pathfinder.h"
#include "Core/Input.h"
#include "Core/AIBehavior/ActionNode.h"
#include <iostream>


AIGameScene::
    ~AIGameScene()
{
}
void AIGameScene::Init()
{
    Scene::Init();

    auto keyEvent = BIND_EVENT_FN(AIGameScene::OnInput);
    Input::AddListener(keyEvent);
}
void AIGameScene::OnInput(int input)
{
    if (std::tolower(input) == 'd')
    {
        // camera->MoveCamera(Vector2(1, 0));
    }
}
void AIGameScene::Start()
{
    Scene::Start();
    playerShip = new PlayerShip(*this);
    enemy = new Enemy(*this);
    // AddGameObject(playerShip, Vector2(15, 5));
    // AddGameObject(enemy, Vector2(5, 12));

    // AddGameObject(new Brick(*this), Vector2(5, 5));
    // AddGameObject(new Brick(*this), Vector2(12, 12));
    // AddGameObject(new Brick(*this), Vector2(17, 5));
    // AddGameObject(new Brick(*this), Vector2(23, 12));
    // AddGameObject(new Brick(*this), Vector2(28, 5));
    auto root = std::make_shared<SelectorNode>("Selector 1");

    auto sequence1 = std::make_shared<SequenceNode>("Sequence 1");
    sequence1->addChild(std::make_shared<ConditionNode>("Condition A"));
    sequence1->addChild(std::make_shared<ActionNode>("Action A"));
    sequence1->addChild(std::make_shared<FailNode>("Failure node"));

    auto sequence2 = std::make_shared<SequenceNode>("Sequence 2");
    sequence2->addChild(std::make_shared<ConditionNode>("Condition C"));
    sequence2->addChild(std::make_shared<ActionNode>("Action D"));

    root->addChild(sequence1);
    root->addChild(sequence2);

    BehaviorTree tree(root);
    tree.Update();
    std::cin.get();
    tree.Update();
    
    m_Linedrawer = new LineDrawer(*this);

    m_Linedrawer->CreateLineParticles(100, 1);
}

void AIGameScene::Update(float deltaTime)
{
    Scene::Update(deltaTime);
    m_Linedrawer->ResetDrawingParticleIndex();
    m_LastTimeSinceCameraMove += deltaTime;
    if (m_LastTimeSinceCameraMove > 0.5f)
    {
        // camera->MoveCameraDown();
        m_LastTimeSinceCameraMove = 0;
    }
    PathNode start(enemy->transform.GetCenterPosition().X, enemy->transform.GetCenterPosition().Y);
    PathNode goal(playerShip->transform.GetCenterPosition().X, playerShip->transform.GetCenterPosition().Y);
    std::vector<PathNode> path = pathfinder->FindPath(start, goal);
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
