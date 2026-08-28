#include "GridCursor.h"
#include "DefenseConfig.h"

GridCursor::GridCursor(Scene &s) : GameObject("GridCursor", s)
{
}

void GridCursor::Init()
{
    hasCollider = false;
    symbol = "+";

    Sprite sprite(CELL_H, std::vector<int>(CELL_W, 0));
    for (int y = 0; y < CELL_H; y++)
    {
        for (int x = 0; x < CELL_W; x++)
        {
            if (y == 0 || y == CELL_H - 1 || x == 0 || x == CELL_W - 1)
                sprite[y][x] = 1;
        }
    }
    SetSprite(sprite);
    overrideColor = GREEN;
}

void GridCursor::MoveTo(int c, int r)
{
    if (c < 0) c = 0;
    if (c > GRID_COLS - 1) c = GRID_COLS - 1;
    if (r < 0) r = 0;
    if (r > GRID_ROWS - 1) r = GRID_ROWS - 1;

    col = c;
    row = r;

    Vector2 pos = CellToWorld(col, row);
    transform.SetPosition(pos.X, pos.Y);
}

void GridCursor::Recolor(bool canPlant, bool hasSun)
{
    if (hasSun)
        overrideColor = YELLOW;
    else
        overrideColor = canPlant ? GREEN : RED;
}
