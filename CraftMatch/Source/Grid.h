#pragma once
const int WIDTH = 10;
const int HEIGHT = 5;
class Grid
{
public:

	void SetGridObject(class GridUnit& gridUnit, int x, int y);
	GridUnit* GetGridUnit(int x, int y) const
	{
		return grid[x][y];
	}
private:
	class GridUnit* grid[WIDTH][HEIGHT];
};

