#include "Sunflower.h"
#include "Systems/SunManager.h"

Sunflower::Sunflower(Scene &s, LaneGrid &grid, SunManager &sunManager)
    : Plant("Sunflower", s, grid, 4.f), sunManager(sunManager)
{
}

void Sunflower::Init()
{
    Plant::Init();
    symbol = "*";
    overrideColor = 3; // yellow
    Sprite sprite = {
        {0, 1, 1, 0},
        {1, 1, 1, 1},
    };
    SetSprite(sprite);
}

void Sunflower::Update(float deltaTime)
{
    sunTimer += deltaTime;
    if (sunTimer >= SUN_INTERVAL)
    {
        sunTimer = 0.f;
        sunManager.SpawnAt(Col(), Row());
    }
}
