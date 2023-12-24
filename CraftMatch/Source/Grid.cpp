#include "Grid.h"

void Grid::SetGridObject(GridUnit& gridUnit, int x, int y)
{
	grid[x][y] = &gridUnit;
}
