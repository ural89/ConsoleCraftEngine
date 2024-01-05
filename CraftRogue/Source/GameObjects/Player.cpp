#include "Player.h"
#include "Core/Component/PlayerController.h"
#include "Weapons/PlasmaGun.h"
#include <memory>
#include "Core/Scene.h"
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

    PlasmaGun *plasmaGun = new PlasmaGun(GetCurrentScene());
    GetCurrentScene().AddGameObject(plasmaGun), startPosition;
    plasmaGun->transform.SetParent(transform);
    plasmaGun->transform.Position = startPosition;
    GetCurrentScene().uiHandler->RemoveString(debugUIDataPtr);
}