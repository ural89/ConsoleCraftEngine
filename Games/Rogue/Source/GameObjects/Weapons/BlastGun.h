#pragma once

#include "GameObjects/Weapons/Weapon.h"

class BlastGun : public Weapon
{
public:
    BlastGun(class Scene &scene) : Weapon(scene)
    {
    }
    void Init() override;
    void Fire(GameObject &targetGameObject) override;
    void Upgrade() override
    {
        numberOfBullets++;
        numberOfBullets = numberOfBullets > 10 ? 10 : numberOfBullets;
    }

private:
    int numberOfBullets = 4;
};