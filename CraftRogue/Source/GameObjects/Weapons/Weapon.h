#pragma once
#include "Core/GameObject.h"
#include "CoreStructs/Vector.h"
class Weapon : public GameObject
{
public:
    Weapon(class Scene& scene) : GameObject("Weapon", scene)
    {

    }
  
    virtual void StopWeapon(){}
    virtual void Fire(Vector2 fireDirection){}
    virtual void Fire(GameObject& targetGameObject){}
    
};