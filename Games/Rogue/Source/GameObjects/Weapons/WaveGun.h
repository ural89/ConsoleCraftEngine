#pragma once

#include "GameObjects/Weapons/Weapon.h"

class WaveGun : public Weapon
{
public:
    WaveGun(class Scene &scene) : Weapon(scene)
    {
        targetGameObject = nullptr;
    }
    ~WaveGun()
    {
    }
    void Init() override;
    void Update(float deltaTime) override;
    void Fire(GameObject &targetGameObject) override;
    void Upgrade() override
    {
        damageTime -= 0.1f;
        damageTime = damageTime < 0.5f ? 0.5f : damageTime;
    }
    void StopWeapon() override;

private:
    bool isFiring = false;
    float damage = 1;
    float damageTime = 1;
    float fireDuration = 0;
    GameObject *targetGameObject;
};