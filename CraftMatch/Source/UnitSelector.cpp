#include "UnitSelector.h"
#include <functional>
#include <Core/Input.h>
#include "GameObjects/GridUnit.h"
#include "Grid.h"
#include <iostream>
UnitSelector::UnitSelector(Grid& grid) : grid(&grid)
{
	auto inputEvent = std::bind(&UnitSelector::OnInput, this, std::placeholders::_1);
	Input::AddListener(inputEvent);
}

void UnitSelector::OnInput(int input)
{
	if (tolower(input) == 'd')
	{
		selectedX++;
	}
	else if (tolower(input) == 'a')
	{
		selectedX--;
	}
	else if (tolower(input) == 's')
	{
		selectedY++;
	}
	else if (tolower(input) == 'w')
	{
		selectedY--;
	}
	UpdateSelectUnit();
}

void UnitSelector::UpdateSelectUnit()
{
	grid->GetGridUnit(selectedX, selectedY)->OnSelected();
}
