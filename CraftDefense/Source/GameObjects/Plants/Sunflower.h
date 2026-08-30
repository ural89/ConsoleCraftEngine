#pragma once
#include "GameObjects/Plants/Plant.h"

class Sunflower : public Plant
{
public:
    Sunflower(class Scene &s, class LaneGrid &grid, class SunManager &sunManager);

    void Init() override;
    void Update(float deltaTime) override;

private:
    SunManager &sunManager;
    float sunTimer = 0.f;
    static constexpr float SUN_INTERVAL = 10.f;
};
