#include "Plant.h"
#include "Grid/LaneGrid.h"

Plant::Plant(std::string &&n, Scene &s, LaneGrid &grid, float maxHealth)
    : GameObject(std::move(n), s), grid(grid), health(maxHealth), maxHealth(maxHealth)
{
}

void Plant::Init()
{
    hasCollider = false;
}

void Plant::TakeBite(float dmg)
{
    health -= dmg;
    if (health <= 0.f)
        OnDied();
}

void Plant::OnDied()
{
    grid.Clear(col, row);
    Destroy();
}
