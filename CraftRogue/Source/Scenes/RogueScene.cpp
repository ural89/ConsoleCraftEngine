#include "RogueScene.h"
#include "../GameObjects/Player.h"
#include "../GameObjects/EnemyRogue.h"
#include "CoreStructs/Vector.h"
void RogueScene::Init()
{
    AddGameObject(new Player(*this), Vector2(30, 10));
    
    srand(static_cast<unsigned int>(time(nullptr)));
    SpawnEnemy();
}

void RogueScene::Update(float deltaTime)
{
    Scene::Update(deltaTime);
    // if (numberOfEnemyToSpawn > 0)
    if (!isPaused)
        spawnDurationPassed += deltaTime;

    if (spawnDurationPassed >= spawnTime)
    {
        spawnDurationPassed = 0;
        SpawnEnemy();
    }
}

void RogueScene::SpawnEnemy()
{
    numberOfEnemyToSpawn--;

    int edge = rand() % 4;

    int xPos, yPos;

    switch (edge)
    {
    case 0: // Top edge
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
    case 3: // Left edge
        xPos = 0;
        yPos = rand() % SCREENHEIGHT;
        break;
    }
   
    AddGameObject(new EnemyRogue(*this), Vector2(xPos, yPos));
}
