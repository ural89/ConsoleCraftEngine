#pragma once
#include "Core/GameObject.h"
#include "Core/UIHandler.h"
#include "Core/Event.h"
#include <functional>
class Player : public GameObject
{
public:
    Player(class Scene &scene) : GameObject("Player", scene) {}
    ~Player();
    
    void Init() override;

    void OnKeyPressed(int input);
    void UnlockWeapon(int index);


private:

    UIData scoreUIData;
    std::shared_ptr<UIData> scoreUIDataPtr;

    void InitializeWeapon(Vector2 &startPosition);
    void RecievedEvent(Event& e);
    void Update(float deltaTime) override;
    void OnCollided(GameObject& other) override;
    class PlayerUpgradeComponent* playerUpgradeComponent;

	std::function<void(int)> inputEvent;

    int weaponIndex = 0;

    std::vector<int> usableWeaponsIndex;
    std::vector<class Weapon*> weapons;

    bool canFire = true;
    float fireDuration = 0;
    float fireRate = 0.5f;

    int score = 0;
};