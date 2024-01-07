#include "Player.h"
#include "Weapons/PlasmaGun.h"
#include "Weapons/WaveGun.h"
#include "../Components/PlayerUpgradeComponent.h"
#include <memory>

#include "Core/Scene.h"
#include "Core/Input.h"
#include "Core/Component/PlayerController.h"
#include "Core/EventDispatcher.h"
Player::~Player()
{
    
	weapons.clear();
    Input::RemoveListener(inputEvent);
    
}
void Player::Init()
{
    scoreUIData.position = Vector2(0, SCREENHEIGHT - 1);
    scoreUIData.text = "Score: " + std::to_string(score);
    scoreUIDataPtr = std::make_shared<UIData>(scoreUIData);
    GetCurrentScene().uiHandler->AddString(scoreUIDataPtr);

    std::function<void(Event &)> OnRecievedEvent = std::bind(&Player::RecievedEvent, this, std::placeholders::_1);
    EventDispatcher::AddListener(OnRecievedEvent);

    PlayerController *playerController = new PlayerController(*this, 0);
    AddComponent(playerController);
    playerUpgradeComponent = new PlayerUpgradeComponent(*this);
    AddComponent(playerUpgradeComponent);

    sprite = {{4, 4, 4},
              {1, 1, 1},
              {1, 2, 1},
               };
    Vector2 startPosition = transform.Position;

    InitializeWeapon(startPosition);

    inputEvent = std::bind(&Player::OnKeyPressed, this, std::placeholders::_1);
    Input::AddListener(inputEvent);
}
void Player::OnKeyPressed(int input)
{
    if (!GetCurrentScene().isPaused)
    {
        if (input == SPACEBAR && canFire)
        {
            canFire = false;
            weaponIndex++;
            weaponIndex = weaponIndex % weapons.size();
            Vector2 StartPoint = transform.Position;
            auto nearestEnemy = GetCurrentScene().FindNearestGameObject(transform, "Enemy");
            if (nearestEnemy != nullptr)
            {

                Vector2 TargetPoint = nearestEnemy->transform.Position;

                Vector2 FireDirection = TargetPoint - StartPoint;
                FireDirection.Normalize();
                weapons[weaponIndex]->Fire(*nearestEnemy);
                weapons[weaponIndex]->Fire(FireDirection);
            }
        }
	}
	else if (GetComponent<PlayerUpgradeComponent>()->isInUpgrade)
	{
        if (input == 49)
        {
            UnlockWeapon(0);
        }
        else if (input == 50)
        {
            UnlockWeapon(1);
        }
	}
}
void Player::RecievedEvent(Event &e)
{
    switch (e.GetEventType())
    {
    case EventType::OnEnemyKilled:
        playerUpgradeComponent->AddExperience(1);
        score++;
        scoreUIDataPtr->text = "Score: " + std::to_string(score);
        break;
    }
}
void Player::Update(float deltaTime)
{
    if (!canFire)
    {
        fireDuration += deltaTime;
        if (fireDuration >= fireRate)
        {
            fireDuration = 0;
            canFire = true;
        }
    }
}
void Player::OnCollided(GameObject &other)
{
    if(other.name == "Enemy")
    {
        GetComponent<PlayerController>()->RemoveListenerForInput();
        GetCurrentScene().hasGameOver = true;
        Destroy();
        return;
    }
}
void Player::UnlockWeapon(int index)
{
    switch (index)
    {
    case 0:
        weaponIndex = 0;
        break;
    case 1:
        weaponIndex = 1;
        break;
    }
}
void Player::InitializeWeapon(Vector2 &startPosition)
{

    Weapon *plasmaWeapon = new PlasmaGun(GetCurrentScene());
    GetCurrentScene().AddGameObject(plasmaWeapon), startPosition;
    plasmaWeapon->transform.SetParent(transform);
    plasmaWeapon->transform.Position = startPosition;
    weapons.push_back(plasmaWeapon);
   
    Weapon *waveGun = new WaveGun(GetCurrentScene());
    GetCurrentScene().AddGameObject(waveGun), startPosition;
    waveGun->transform.SetParent(transform);
    waveGun->transform.Position = startPosition;
    weapons.push_back(waveGun);
}
