#include "Grid.h"
#include "GameObjects/GridUnit.h"
void Grid::SetGridObject(GridUnit& gridUnit, int x, int y) 
{

	grid[x][y] = &gridUnit;
}

void Grid::FillBlanks()
{
	for (int i = 0; i < WIDTH; i++)
		for (int j = 0; j < HEIGHT; j++)
		{

			if (j > 1)
			{
				auto checkUnit = grid[i][j];
				if (checkUnit->UnitItem == nullptr) //TODO: fix
				{
					checkUnit->UnitItem = grid[i][j - 1]->UnitItem;
					checkUnit->UnitItem->transform.Position = checkUnit->GetItemSlot();
					grid[i][j - 1]->UnitItem = nullptr;

				}
			}
		}
}
