#pragma once
#include "Core/Scene.h"
class BreakerScene : public Scene
{
public:
    void Init() override;
    void Update(float deltaTime) override;
private:
    void MoveCamera(int input);
};