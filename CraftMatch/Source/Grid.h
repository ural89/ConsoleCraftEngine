#pragma once

class Grid
{
public:

	void SetGridObject(class GridUnit& gridUnit, int x, int y);
	GridUnit* GetGridUnit(int x, int y) const
	{
		return grid[x][y];
	}
private:
	class GridUnit* grid[10][5];
};

