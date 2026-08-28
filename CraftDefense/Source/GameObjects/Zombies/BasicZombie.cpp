#include "BasicZombie.h"

BasicZombie::BasicZombie(Scene &s, LaneGrid &grid)
    : Zombie("Zombie", s, grid, 8.f, 1.5f, 1.f, 0.5f)
{
}

void BasicZombie::Init()
{
    symbol = "Z";
    overrideColor = 250;
    Sprite sprite = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1},
    };
    SetSprite(sprite);

    Zombie::Init();
}
