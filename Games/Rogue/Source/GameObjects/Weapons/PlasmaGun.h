#pragma once
#include "Weapon.h"
#include "CoreStructs/Vector.h"

class PlasmaGun : public Weapon
{
public:
    PlasmaGun(class Scene &scene) : Weapon(scene) {}
    ~PlasmaGun() {}
    void Upgrade() override
    {
        damage++;
    }
    void Init() override;
    
    void Fire(GameObject& targetGameObject) override;

private:

};