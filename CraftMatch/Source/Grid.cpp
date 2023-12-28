#include "Grid.h"
#include "GameObjects/GridUnit.h"
#include "GameObjects/SpadesItem.h"
#include "GameObjects/HeartItem.h"
#include "GameObjects/DiamondItem.h"
#include "GameObjects/ClubItem.h"

void Grid::SetGridObject(GridUnit& gridUnit, int x, int y) 
{

	grid[x][y] = &gridUnit;
}

void Grid::FillBlanks()
{
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = HEIGHT - 1; j >= 0; j--)
		{
			auto checkUnit = grid[i][j];
			
			if (checkUnit->UnitItem == nullptr)
			{
				
					if (j == 0) //at the top of the screen
					{
						CreateRandomItem(i, j);
					}
					else if(grid[i][j - 1]->UnitItem != nullptr) //drop item one down
					{
						checkUnit->UnitItem = grid[i][j - 1]->UnitItem;
						checkUnit->UnitItem->transform.Position = (checkUnit->GetItemSlot());
						//checkUnit->UnitItem->SetTargetPosition(checkUnit->GetItemSlot());
						grid[i][j - 1]->UnitItem = nullptr;
					}
			}
			
		}
	}
	hasRefreshedAfterBlown = false;
	timePassed = 0;

}

void Grid::RefreshItemRenders()
{
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = HEIGHT - 1; j >= 0; j--)
		{
			auto checkUnit = grid[i][j];
			checkUnit->UnitItem->transform.HasClearedFlag = false;
		}
	}
	hasRefreshedAfterBlown = true;
}

void Grid::CreateItemsAtStart()
{
	for (int i = 0; i < WIDTH; i++)
		for (int j = 0; j < HEIGHT; j++)
		{
				CreateRandomItem(i, j);
		}
}

void Grid::CreateRandomItem(int i, int j)
{
	Item* unitItem = nullptr;
	int gridUnitType = rand() % 4;
	switch (gridUnitType)
	{
	case SPADES:
		unitItem = new SpadesItem(*scene);
		break;
	case HEART:
		unitItem = new HeartItem(*scene);
		break;
	case CLUB:
		unitItem = new ClubItem(*scene);
		break;
	case DIAMOND:
		unitItem = new DiamondItem(*scene);
		break;
	}
	auto gridUnit = GetGridUnit(i, j);
	scene->AddGameObject(unitItem, gridUnit->GetItemSlot());
	gridUnit->UnitItem = unitItem;

	

}

void Grid::Update(float deltaTime)
{
	if (!hasRefreshedAfterBlown)
	{
		if (timePassed > 1)
		{
			//RefreshItemRenders();
			
		}
	}
	timePassed += deltaTime;
}
