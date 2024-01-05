#pragma once
#include "Weapon.h"
#include "CoreStructs/Vector.h"

class PlasmaGun : public Weapon
{
public:
    PlasmaGun(class Scene &scene) : Weapon(scene) {}
    ~PlasmaGun() {}
    void Init() override;
    
    void Fire(Vector2 fireDirection) override;

private:

};