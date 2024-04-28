#pragma once
#include "../GameObject.h"

class RopeParticle : public GameObject
{
public:
    RopeParticle(class Scene &scene) : GameObject("RopeParticle", scene) {}
    void Init() override
    {
        sprite = {{1}};
        symbol = "O";
    }
    bool isFixed = false;
};