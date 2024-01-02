#include "BreakerScene.h"
#include "../GameObjects/Breaker.h"
#include "../GameObjects/Ball.h"
#include "../GameObjects/Brick.h"
#include <functional>
#include "Core/Input.h"
void BreakerScene::Init()
{
    int offsetX = 5;
    int offsetY = 2;
    int brickHeight = 5;
    int brickWidth = 5;
    AddGameObject(new Breaker(*this), Vector2(10, SCREENHEIGHT - 2));
    AddGameObject(new Ball(*this), Vector2(10, 12));
    for (int j = 0; j < 2; j++)
        for (int i = 0; i < 6; i++)
        {
            AddGameObject(new Brick(*this), Vector2(offsetX + i * brickWidth, offsetY + j * brickWidth));
        }
    camera->isMoving = true;
    //camera->MoveCamera(Vector2(4, 0));

    auto event = std::bind(&BreakerScene::MoveCamera, this, std::placeholders::_1);
    Input::AddListener(event);
}

void BreakerScene::Update(float deltaTime)
{
    Scene::Update(deltaTime);
}

void BreakerScene::MoveCamera(int input)
{
    if (tolower(Input::GetKeyDown()) == 'k')
    {
        camera->MoveCamera(Vector2(5, 0));
    }
    if (tolower(Input::GetKeyDown()) == 'h')
    {
        camera->MoveCamera(Vector2(-5, 0));
    }
    if (tolower(Input::GetKeyDown()) == 'j')
    {
        camera->MoveCamera(Vector2(0, 5));
    }
    if (tolower(Input::GetKeyDown()) == 'u')
    {
        camera->MoveCamera(Vector2(0, -5));
    }
}
