#include "BreakerScene.h"
#include "../GameObjects/Breaker.h"
#include "../GameObjects/Ball.h"


void BreakerScene::Init()
{
    AddGameObject(new Breaker(*this), Vector2(10,SCREENHEIGHT - 2));
    AddGameObject(new Ball(*this), Vector2(10, 8));
}

void BreakerScene::Update(float deltaTime)
{
    Scene::Update(deltaTime);
}