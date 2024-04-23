#pragma once
#include "Core/GameObject.h"
#include "CoreStructs/Vector.h"
class Weapon : public GameObject
{
public:
    Weapon(class Scene& scene) : GameObject("Weapon", scene)
    {

    }
    virtual void Upgrade(){};
    virtual void StopWeapon(){}
    virtual void Fire(GameObject& targetGameObject){}
protected:
    float damage = 1;
    
};