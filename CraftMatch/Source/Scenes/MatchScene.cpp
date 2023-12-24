#include "MatchScene.h"
#include "../GameObjects/GridUnit.h"
#include "../Grid.h"
#include "../UnitSelector.h"
#include "../GameObjects/SpadesItem.h"
#include "../GameObjects/HeartItem.h"
#include "../GameObjects/DiamondItem.h"
#include "../GameObjects/ClubItem.h"
MatchScene::~MatchScene()
{
	delete grid;

}
void MatchScene::Init()
{
	CreateGrid(WIDTH, HEIGHT);
	CreateItems();
}

void MatchScene::CreateGrid(int width, int height)
{
	int gridOffsetX = 15;
	int gridOffsetY = 5;
	grid = new Grid();
	UnitSelector* unitSelector = new UnitSelector(*grid);
	auto gridUnit = new GridUnit(*this);

	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
		{
			auto gridUnit = new GridUnit(*this);
			AddGameObject(gridUnit, Vector2(5 * i + gridOffsetX, 4 * j + gridOffsetY));
			grid->SetGridObject(*gridUnit, i, j);
		}
}

void MatchScene::CreateItems()
{

	for (int i = 0; i < WIDTH; i++)
		for (int j = 0; j < HEIGHT; j++)
		{
			auto gridUnit = grid->GetGridUnit(i, j);
			auto unitItem = new HeartItem(*this);
			AddGameObject(unitItem, gridUnit->GetItemSlot());
			gridUnit->UnitItem = unitItem;
		}
	
}


