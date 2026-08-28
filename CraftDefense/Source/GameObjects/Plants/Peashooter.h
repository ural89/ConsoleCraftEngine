#pragma once
#include "GameObjects/Plants/Plant.h"

class Peashooter : public Plant
{
public:
    Peashooter(class Scene &s, class LaneGrid &grid);

    void Init() override;
    void Update(float deltaTime) override;

private:
    float fireTimer = 0.f;
    static constexpr float FIRE_INTERVAL = 1.5f;
};
