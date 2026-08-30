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
    Sprite sprite = {
        {0, 2, 0, 0},
        {3, 3, 3, 3},
    };
    SetSprite(sprite);
}

void Sunflower::Update(float deltaTime)
{
    sunTimer += deltaTime;
    if (sunTimer >= SUN_INTERVAL)
    {
        sunTimer = 0.f;
        sunManager.SpawnAt(Col(), Row() );
    }
}
