#include "Grid.h"
#include "GameObjects/GridUnit.h"
#include "GameObjects/SpadesItem.h"
void Grid::SetGridObject(GridUnit& gridUnit, int x, int y) 
{

	grid[x][y] = &gridUnit;
}

void Grid::FillBlanks()
{
	for (int i = 0; i < WIDTH; i++)
		for (int j = HEIGHT - 1; j >= 0 ; j--)
		{
			auto checkUnit = grid[i][j];
			
			if (checkUnit->UnitItem == nullptr && grid[i][j - 1]->UnitItem != nullptr) 
			{
				if (j == 0) //at the top of the screen
				{
					auto newItem = new SpadesItem(*scene);
					scene->AddGameObject(newItem, grid[i][j]->GetItemSlot());
					grid[i][j]->UnitItem = newItem;
				}
				else
				{
					checkUnit->UnitItem = grid[i][j - 1]->UnitItem;
					checkUnit->UnitItem->transform.Position = checkUnit->GetItemSlot();
					grid[i][j - 1]->UnitItem = nullptr;
				}
			}
		}
}
