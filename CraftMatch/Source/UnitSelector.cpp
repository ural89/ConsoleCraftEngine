#include "UnitSelector.h"

#include <Core/Input.h>
#include "GameObjects/GridUnit.h"


UnitSelector::UnitSelector(Grid& grid) : grid(&grid)
{
	
	auto inputEvent = std::bind(&UnitSelector::OnInput, this, std::placeholders::_1);
	Input::AddListener(inputEvent);
	
}

void UnitSelector::OnInput(int input)
{
	UnselectUnit(selectedX, selectedY);
	if (input == SPACEBAR)
	{
		isSelecting = !isSelecting;
		if (!isSelecting)
		{
			ClearSelectedUnits();
		}
	}

	if (tolower(input) == 'd')
	{
		if (selectedX < WIDTH - 1)
		{
			if (isSelecting)
				if (GetItemType(selectedX + 1, selectedY) != firstSelectedItemType)
					return;
			selectedX++;
		}
	}
	else if (tolower(input) == 'a')
	{
		if (selectedX > 0)
		{
			if (isSelecting)
				if (GetItemType(selectedX - 1, selectedY) != firstSelectedItemType)
					return;
			selectedX--;
		}
	}
		else if (tolower(input) == 's')
		{
			if (selectedY < HEIGHT - 1)
			{
				if (isSelecting)
					if (GetItemType(selectedX, selectedY + 1) != firstSelectedItemType)
						return;
				selectedY++;
				
			}
		}
		else if (tolower(input) == 'w')
		{
			if (selectedY > 0)
			{
				if (isSelecting)
					if (GetItemType(selectedX, selectedY - 1) != firstSelectedItemType)
						return;
				selectedY--;
				
			}
		}
		SelectUnit(selectedX, selectedY);
	
}
void UnitSelector::SelectUnit(int x, int y)
{
	if (isSelecting)
	{
		auto* gridUnit = grid->GetGridUnit(x, y);
		gridUnit->OnCreatingLine();
		if (std::find(selectedUnits.begin(), selectedUnits.end(), gridUnit) == selectedUnits.end())
			selectedUnits.push_back(gridUnit);
		else
		{
			//gridUnit->OnUnselected();//TODO:
		}
		
	}
	else
	{
		grid->GetGridUnit(selectedX, selectedY)->OnSelected();
		firstSelectedItemType = GetItemType(selectedX, selectedY);
		
	}
}

void UnitSelector::UnselectUnit(int x, int y)
{
	if (!isSelecting)
	{
		grid->GetGridUnit(x, y)->OnUnselected();
	}
}

void UnitSelector::ClearSelectedUnits()
{
	for (auto* unit : selectedUnits)
	{
		unit->OnUnselected();
		unit->OnSelectionBlown();
		grid->FillBlanks();
	}

	selectedUnits.clear();  // Clear the deque
}

int UnitSelector::GetItemType(int x, int y)
{
	return grid->GetGridUnit(x, y)->UnitItem->itemType;
}
