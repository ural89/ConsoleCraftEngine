#include "LaneGrid.h"
#include "GameObjects/Plants/Plant.h"
#include "GameObjects/Zombies/Zombie.h"
#include <algorithm>
#include <limits>

bool LaneGrid::IsFree(int col, int row) const
{
    return cells[col][row] == nullptr;
}

bool LaneGrid::Place(Plant *p, int col, int row)
{
    if (!IsFree(col, row))
        return false;

    cells[col][row] = p;
    p->SetCell(col, row);
    return true;
}

void LaneGrid::Clear(int col, int row)
{
    cells[col][row] = nullptr;
}

Plant *LaneGrid::At(int col, int row) const
{
    return cells[col][row];
}

void LaneGrid::RegisterZombie(Zombie *z)
{
    lanes[z->Lane()].push_back(z);
}

void LaneGrid::UnregisterZombie(Zombie *z)
{
    auto &v = lanes[z->Lane()];
    v.erase(std::remove(v.begin(), v.end(), z), v.end());
}

Zombie *LaneGrid::FirstZombieAheadOf(int lane, float x) const
{
    Zombie *nearest = nullptr;
    float nearestX = std::numeric_limits<float>::max();

    for (auto z : lanes[lane])
    {
        if (z->transform.Position.X > x && z->transform.Position.X < nearestX)
        {
            nearest = z;
            nearestX = z->transform.Position.X;
        }
    }

    return nearest;
}

Plant *LaneGrid::FrontPlantFor(const Zombie &z) const
{
    int row = z.Lane();
    float zx = z.transform.Position.X;
    float zw = static_cast<float>(z.GetWidth());

    for (int col = 0; col < GRID_COLS; col++)
    {
        Plant *p = cells[col][row];
        if (!p)
            continue;

        float px = p->transform.Position.X;
        float pw = static_cast<float>(p->GetWidth());

        if (zx < px + pw && px < zx + zw)
            return p;
    }

    return nullptr;
}
