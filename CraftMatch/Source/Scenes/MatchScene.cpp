#include "MatchScene.h"
#include "../GameObjects/GridUnit.h"

void MatchScene::Init()
{
	CreateGrid(10, 5);
}

void MatchScene::CreateGrid(int width, int height)
{
	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
		{
			auto gridUnit = new GridUnit(*this);
			AddGameObject(gridUnit, Vector2(5 * i, 4 * j));
			grid[i][j] = gridUnit;
		}
}
