#pragma once
#include "Core/GameObject.h"
#include "Core/UIHandler.h"
class Player : public GameObject
{
public:
    Player(class Scene &scene) : GameObject("Player", scene) {}
    void Init() override;

private:
    UIData debugUIData;
    std::shared_ptr<UIData> debugUIDataPtr;
};