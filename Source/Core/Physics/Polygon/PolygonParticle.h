#pragma once
#include "../../../Core.h"
#include "../../GameObject.h"
#include "../../Component/RigidbodyComponent.h"
#include "../../Component/SpringComponent.h"
class GE_API PolygonParticle : public GameObject
{
public:
    PolygonParticle(class Scene &scene) : GameObject("PolygonParticle", scene)
    {
        sprite = {{1}};
        symbol = "X";
    }
    virtual ~PolygonParticle() {}
    void Init() override;
    bool isFixed = false;
    void OnReady();
};