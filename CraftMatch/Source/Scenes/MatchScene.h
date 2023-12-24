#pragma once
#include "Core\Scene.h"
class MatchScene : public Scene
{
public:
	void Init() override;
	class GridUnit* grid[10][5];
private:
	void CreateGrid(int width, int height);
};

