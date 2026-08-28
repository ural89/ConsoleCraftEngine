#pragma once
#include "DefenseConfig.h"
#include <vector>

class LaneGrid
{
public:
    bool IsFree(int col, int row) const;
    bool Place(class Plant *p, int col, int row);
    void Clear(int col, int row);
    class Plant *At(int col, int row) const;

    void RegisterZombie(class Zombie *z);
    void UnregisterZombie(class Zombie *z);
    class Zombie *FirstZombieAheadOf(int lane, float x) const;
    class Plant *FrontPlantFor(const class Zombie &z) const;

private:
    class Plant *cells[GRID_COLS][GRID_ROWS] = {};
    std::vector<class Zombie *> lanes[GRID_ROWS];
};
