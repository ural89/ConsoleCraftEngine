#include "RTSScene.h"
#include "GameObjects/Unit.h"

void RTSScene::Init()
{
    AddGameObject(new Unit(*this), Vector2(5,5));
}

void RTSScene::Update(float deltaTime)
{
    Scene::Update(deltaTime);
}

