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
	grid->CreateItemsAtStart();
}

void MatchScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);
	grid->Update(deltaTime);
	unitSelector->Update(deltaTime);
}

void MatchScene::CreateGrid(int width, int height)
{
	int gridOffsetX = 15;
	int gridOffsetY = 5;
	grid = new Grid(*this);
	unitSelector = new UnitSelector(*grid);
	auto gridUnit = new GridUnit(*this);

	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
		{
			auto gridUnit = new GridUnit(*this);
			AddGameObject(gridUnit, Vector2(5 * i + gridOffsetX, 4 * j + gridOffsetY));
			grid->SetGridObject(*gridUnit, i, j);
		}
}




