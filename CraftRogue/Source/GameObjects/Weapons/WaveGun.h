#pragma once
#include "Weapon.h"

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
    void StopWeapon() override;

private:
    bool isFiring = false;
    float fireDuration = 0;
    GameObject *targetGameObject;
};