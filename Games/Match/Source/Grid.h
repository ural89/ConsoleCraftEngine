#pragma once
#include "Core/Scene.h"
const int WIDTH = 10;
const int HEIGHT = 5;
class Grid
{
public:
	Grid(Scene &scene) : scene(&scene) {}
	void SetGridObject(class GridUnit &gridUnit, int x, int y);
	GridUnit *GetGridUnit(int x, int y) const
	{
		return grid[x][y];
	}
	void FillBlanks();
	void RefreshItemRenders();
	void CreateItemsAtStart();
	void CreateRandomItem(int i, int j);
	Scene &GetScene() const
	{	
		return *scene;
	}
	void Update(float deltaTime);

private:
	Scene *scene;
	class GridUnit *grid[WIDTH][HEIGHT];
	float timePassed = 0;
	bool hasRefreshedAfterBlown = false;
};
