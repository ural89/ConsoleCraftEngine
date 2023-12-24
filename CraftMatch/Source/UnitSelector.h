#pragma once
#include "Grid.h"
#include <deque>
class UnitSelector
{
public:

	UnitSelector(Grid& grid);
private:
	int selectedX = 0;
	int selectedY = HEIGHT - 1;

	Grid* grid;
	std::deque<class GridUnit*> selectedUnits;

	bool isSelecting = false;

	void OnInput(int input);
	void SelectUnit(int x, int y);
	void UnselectUnit(int x, int y);
	void ClearSelectedUnits();
};

