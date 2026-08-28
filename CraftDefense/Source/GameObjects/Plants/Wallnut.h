#pragma once
#include "GameObjects/Plants/Plant.h"

class Wallnut : public Plant
{
public:
    Wallnut(class Scene &s, class LaneGrid &grid);

    void Init() override;
    void Update(float deltaTime) override;

private:
    void RefreshSprite(int stage);
    int lastStage = -1;
};
