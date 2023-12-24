#include "MatchScene.h"
#include "../GameObjects/GridUnit.h"
#include "../Grid.h"
#include "../UnitSelector.h"
MatchScene::~MatchScene()
{
	delete grid;

}
void MatchScene::Init()
{
	CreateGrid(WIDTH, HEIGHT);

}

void MatchScene::CreateGrid(int width, int height)
{
	grid = new Grid();
	UnitSelector* unitSelector = new UnitSelector(*grid);

	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
		{
			auto gridUnit = new GridUnit(*this);
			AddGameObject(gridUnit, Vector2(5 * i, 4 * j));
			grid->SetGridObject(*gridUnit, i, j);
		}
}


