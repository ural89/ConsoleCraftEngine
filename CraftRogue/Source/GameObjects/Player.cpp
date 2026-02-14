#include "Player.h"

#include "Weapons/PlasmaGun.h"
#include "Weapons/WaveGun.h"
#include "Weapons/BlastGun.h"

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
    usableWeaponsIndex.clear();
    weapons.clear();
    weaponIndex = 0;
    score = 0;
    EventDispatcher::RemoveListener(OnRecievedEvent);
}
void Player::Init()
{
    scoreUIData.position = Vector2(0, SCREENHEIGHT - 1);
    scoreUIData.text = "Score: " + std::to_string(score);
    scoreUIDataPtr = std::make_shared<UIData>(scoreUIData);
    GetCurrentScene().uiHandler->AddString(scoreUIDataPtr);

    usableWeaponsIndex.push_back(0);

    OnRecievedEvent = std::bind(&Player::RecievedEvent, this, std::placeholders::_1);
    EventDispatcher::AddListener(OnRecievedEvent);

    PlayerController *playerController = new PlayerController(*this, 0);
    AddComponent(playerController);
    // playerUpgradeComponent = new PlayerUpgradeComponent(*this);
    playerUpgradeComponent = AddComponent<PlayerUpgradeComponent>();
    symbol = 'O';
    Sprite sprite = {
        {4, 4, 4},
        {1, 1, 1},
        {1, 2, 1},
    };
    SetSprite(sprite);
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

            Vector2 StartPoint = transform.Position;
            auto nearestEnemy = GetCurrentScene().FindNearestGameObject(transform, "Enemy");
            if (nearestEnemy != nullptr)
            {

                weapons[usableWeaponsIndex[weaponIndex % usableWeaponsIndex.size()]]->Fire(*nearestEnemy);
            }
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
    if (other.name == "Enemy")
    {
        GetComponent<PlayerController>()->RemoveListenerForInput();
        GetCurrentScene().hasGameOver = true;
        Destroy();
        return;
    }
}
void Player::UnlockWeapon(int index)
{

    if (std::find(usableWeaponsIndex.begin(), usableWeaponsIndex.end(), index) == usableWeaponsIndex.end())
    {
        usableWeaponsIndex.push_back(index);
    }
    else
    {
        weapons[usableWeaponsIndex[index]]->Upgrade();
    }
}
void Player::InitializeWeapon(Vector2 &startPosition)
{

    Weapon *plasmaWeapon = new PlasmaGun(GetCurrentScene());
    GetCurrentScene().AddGameObject(plasmaWeapon, startPosition);
    plasmaWeapon->transform.SetParent(transform);
    weapons.push_back(plasmaWeapon);

    Weapon *waveGun = new WaveGun(GetCurrentScene());
    GetCurrentScene().AddGameObject(waveGun, startPosition);
    waveGun->transform.SetParent(transform);
    weapons.push_back(waveGun);

    Weapon *blastGun = new BlastGun(GetCurrentScene());
    GetCurrentScene().AddGameObject(blastGun, startPosition);
    blastGun->transform.SetParent(transform);
    weapons.push_back(blastGun);
}
