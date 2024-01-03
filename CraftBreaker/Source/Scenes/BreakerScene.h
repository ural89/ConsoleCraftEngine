#pragma once
#include "Core/Scene.h"
#include "Core/UIHandler.h"
class BreakerScene : public Scene
{
public:
    void Init() override;
    void Update(float deltaTime) override;
private:
    UIData scoreUIData;
    void MoveCamera(int input);
};