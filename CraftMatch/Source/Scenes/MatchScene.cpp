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
			AddGameObject(new GridUnit(*this), Vector2(5 * i, 4 * j));
		}
}
