#pragma once
#include "../../GameObject.h"
#include "../../../Core.h"
class GE_API LineParticle : public GameObject
{
public:
    LineParticle(class Scene &scene) : GameObject("LineParticle", scene)
    {
        hasCollider = false;
        isNavIgnore = true;
    }
    void Init() override
    {
        Sprite sprite = {{1}};
        symbol = "o";
        SetSprite(sprite);
    }
    bool isFixed = false;
};
