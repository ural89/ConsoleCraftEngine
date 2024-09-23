#pragma once
#include "Core/GameObject.h"

class Brick : public GameObject
{
public:
    Brick(class Scene& scene) : GameObject("Brick", scene)
    {

    }
    void Init() override;
};