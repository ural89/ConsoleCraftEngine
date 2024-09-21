#include "EntryScene.h"
#include "../GameObjects/PlayerShip.h"
EntryScene::
~EntryScene()
{

}
void EntryScene::Init()
{
    Scene::Init();
    AddGameObject(new PlayerShip(*this), Vector2(5,5));
}

void EntryScene::Start()
{
    Scene::Start();
}

void EntryScene::Update(float deltaTime)
{
    Scene::Update(deltaTime);
    m_Pathfinding->ShowGameObjects();

}
