#include "Player.h"
#include "Core/Component/PlayerController.h"
#include "Weapons/PlasmaGun.h"
#include <memory>
#include "Core/Scene.h"
#include "Core/Input.h"
void Player::Init()
{
    debugUIData.position = Vector2(0, 29);
    debugUIData.text = "Debug Text";
    debugUIDataPtr = std::make_shared<UIData>(debugUIData);
    GetCurrentScene().uiHandler->AddString(debugUIDataPtr);

    PlayerController *playerController = new PlayerController(*this, 0);
    AddComponent(playerController);
    sprite = {{0, 1, 0},
              {1, 1, 1},
              {1, 1, 1},
              {1, 0, 1}};
    Vector2 startPosition(10, 10);

    InitializeWeapon(startPosition);

    GetCurrentScene().uiHandler->RemoveString(debugUIDataPtr);

    auto inputEvent = std::bind(&Player::OnKeyPressed, this, std::placeholders::_1);
    Input::AddListener(inputEvent);
}
void Player::OnKeyPressed(int input)
{
    if (input == SPACEBAR)
    {
        Vector2 StartPoint = transform.Position;
        auto nearestEnemy = GetCurrentScene().FindNearestGameObject(transform, "Enemy");
        if (nearestEnemy != nullptr)
        {

            Vector2 TargetPoint = nearestEnemy->transform.Position;

            Vector2 FireDirection = TargetPoint - StartPoint;
            FireDirection.Normalize();

            weapon->Fire(FireDirection);
        }
    }
}
void Player::InitializeWeapon(Vector2 &startPosition)
{
    weapon = new PlasmaGun(GetCurrentScene());
    GetCurrentScene().AddGameObject(weapon), startPosition;
    weapon->transform.SetParent(transform);
    weapon->transform.Position = startPosition;
}
