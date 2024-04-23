#pragma once
#include "Core/GameObject.h"

class Breaker : public GameObject
{
public:
    Breaker(class Scene& scene) : GameObject("Breaker", scene)
    {
       
    }
    void Init() override;
    
};