#pragma once
#include "Core/GameObject.h"
#include "Core/UIHandler.h"
#include "Core/Event.h"
class Player : public GameObject
{
public:
    Player(class Scene &scene) : GameObject("Player", scene) {}
    ~Player()
    {
        weapons.clear();
    }
    void Init() override;

    void OnKeyPressed(int input);


private:

    UIData debugUIData;
    std::shared_ptr<UIData> debugUIDataPtr;

    void InitializeWeapon(Vector2 &startPosition);
    void RecievedEvent(Event& e);
    bool hasUsedWaveGun = false;
    class PlayerUpgradeComponent* playerUpgradeComponent;
    class ParticleSource* ps;
    std::vector<class Weapon*> weapons;
};