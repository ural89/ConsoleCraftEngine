#include "RogueScene.h"
#include "../GameObjects/Player.h"
#include "../GameObjects/Enemies/EnemyRogue.h"
#include "../GameObjects/Enemies/EnemyAmeboid.h"
#include "CoreStructs/Vector.h"

const int STANDARDENEMYTYPE = 0;
const int AMEBOIDENEMYTYPE = 1;
void RogueScene::Init()
{
    AddGameObject(new Player(*this), Vector2(30, 10));

    srand(static_cast<unsigned int>(time(nullptr)));
    SpawnEnemy(rand() % 2);
}

void RogueScene::Update(float deltaTime)
{
    Scene::Update(deltaTime);
 
    if (!isPaused)
        spawnDurationPassed += deltaTime;

    if (spawnDurationPassed >= spawnTime)
    {
        spawnDurationPassed = 0;
        SpawnEnemy(rand() % 3);
    }
}

void RogueScene::SpawnEnemy(int enemyType)
{
    numberOfEnemyToSpawn--;

    int edge = rand() % 4;

    int xPos, yPos;

    switch (edge)
    {
    case 3: // Top edge
        xPos = rand() % SCREENWIDTH;
        yPos = 0;
        break;
    case 1: // Right edge
        xPos = SCREENWIDTH;
        yPos = rand() % SCREENHEIGHT;
        break;
    case 2: // Bottom edge
        xPos = rand() % SCREENWIDTH;
        yPos = SCREENHEIGHT;
        break;
    case 0: // Left edge
        xPos = 0;
        yPos = rand() % SCREENHEIGHT;
        break;
    }
    switch (enemyType)
    {
    case 0:
        AddGameObject(new EnemyRogue(*this), Vector2(xPos, yPos));
        break;
    case 1:
        AddGameObject(new EnemyRogue(*this), Vector2(xPos, yPos));

        break;
    case 2:
        AddGameObject(new EnemyAmeboid(*this), Vector2(xPos, yPos));
        break;
    default:
        break;
    }
}
