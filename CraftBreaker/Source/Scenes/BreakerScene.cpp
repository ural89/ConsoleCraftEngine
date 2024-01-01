#include "BreakerScene.h"
#include "../GameObjects/Breaker.h"
#include "../GameObjects/Ball.h"
#include "../GameObjects/Brick.h"

void BreakerScene::Init()
{
    int offsetX = 5;
    int offsetY = 2;
    int brickHeight = 5;
    int brickWidth = 5;
    AddGameObject(new Breaker(*this), Vector2(10,SCREENHEIGHT - 2));
    AddGameObject(new Ball(*this), Vector2(10, 12));
     for (int j = 0; j < 2; j++)
    for (int i = 0; i < 6; i++)
    {
        AddGameObject(new Brick(*this), Vector2(offsetX + i * brickWidth, offsetY + j * brickWidth));
    }
    
}

void BreakerScene::Update(float deltaTime)
{
    Scene::Update(deltaTime);
}