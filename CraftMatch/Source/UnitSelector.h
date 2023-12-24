#pragma once

class UnitSelector
{
public:
	UnitSelector(class Grid& grid);
private:
	int selectedX = 0;
	int selectedY = 0;

	Grid* grid;
	void OnInput(int input);
	void UpdateSelectUnit();
};

