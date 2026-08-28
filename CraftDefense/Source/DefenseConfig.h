#pragma once
#include "CoreStructs/Vector.h"

const int GRID_COLS = 9;
const int GRID_ROWS = 5;
const int CELL_W = 7;   // 9 * 7 = 63 columns of lawn
const int CELL_H = 3;   // 5 * 3 = 15 rows of lawn
const int GRID_X0 = 6;  // lawn spans x = 6 .. 68
const int GRID_Y0 = 3;  // lawn spans y = 3 .. 17
const int SPAWN_X = 76; // zombies enter here, walk left
const int BREACH_X = GRID_X0 - 2;

enum class PlantType
{
    Sunflower,
    Peashooter,
    Wallnut
};

inline Vector2 CellToWorld(int col, int row)
{
    return Vector2(static_cast<float>(GRID_X0 + col * CELL_W), static_cast<float>(GRID_Y0 + row * CELL_H));
}

inline int WorldToLane(float y)
{
    int row = static_cast<int>((y - GRID_Y0) / CELL_H);
    if (row < 0) row = 0;
    if (row > GRID_ROWS - 1) row = GRID_ROWS - 1;
    return row;
}

inline int WorldToCol(float x)
{
    int col = static_cast<int>((x - GRID_X0) / CELL_W);
    if (col < 0) col = 0;
    if (col > GRID_COLS - 1) col = GRID_COLS - 1;
    return col;
}

inline Vector2 LaneSpawnPos(int lane)
{
    return Vector2(static_cast<float>(SPAWN_X), static_cast<float>(GRID_Y0 + lane * CELL_H));
}
