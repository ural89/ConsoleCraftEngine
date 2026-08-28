#include "Wallnut.h"

Wallnut::Wallnut(Scene &s, LaneGrid &grid)
    : Plant("Wallnut", s, grid, 24.f)
{
}

void Wallnut::Init()
{
    Plant::Init();
    symbol = "#";
    overrideColor = 3;
    RefreshSprite(0);
}

void Wallnut::Update(float deltaTime)
{
    float frac = HealthFraction();
    int stage = frac > 0.66f ? 0 : (frac > 0.33f ? 1 : 2);
    if (stage != lastStage)
        RefreshSprite(stage);
}

void Wallnut::RefreshSprite(int stage)
{
    lastStage = stage;

    switch (stage)
    {
    case 0:
        overrideColor = 3;
        SetSprite({
            {1, 1, 1},
            {1, 1, 1},
            {1, 1, 1},
        });
        break;
    case 1:
        overrideColor = 94;
        SetSprite({
            {1, 0, 1},
            {1, 1, 1},
            {1, 0, 1},
        });
        break;
    default:
        overrideColor = 130;
        SetSprite({
            {1, 0, 1},
            {0, 1, 0},
            {1, 0, 1},
        });
        break;
    }
}
