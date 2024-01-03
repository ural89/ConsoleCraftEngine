#include "UnitSelector.h"
#include "Core/UIHandler.h"
#include <Core/Input.h>
#include "GameObjects/GridUnit.h"


UnitSelector::UnitSelector(Grid& grid) : grid(&grid)
{
	scoreUIData.position = Vector2(70, 10);
	scoreUIData.text = "Score: " + std::to_string(score);
	scoreUIDataPtr = std::make_shared<UIData>(scoreUIData);
	grid.GetScene().uiHandler->AddString(scoreUIDataPtr);
	auto inputEvent = std::bind(&UnitSelector::OnInput, this, std::placeholders::_1);
	Input::AddListener(inputEvent);

	
}

void UnitSelector::Update(float deltaTime)
{

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
				{
					if (selectedX < WIDTH - 1&& selectedY < HEIGHT - 1 && GetItemType(selectedX + 1, selectedY - 1) == firstSelectedItemType)
					{
						selectedX++;
						selectedY--;
						SelectUnit(selectedX, selectedY);
					}

					else if (selectedX < WIDTH - 1 && selectedY < HEIGHT - 1 && GetItemType(selectedX + 1, selectedY + 1) == firstSelectedItemType)
					{
						selectedX++;
						selectedY++;
						SelectUnit(selectedX, selectedY);
					}
					return;
				
				}
			selectedX++;
		}
	}
	else if (tolower(input) == 'a')
	{
		if (selectedX > 0)
		{
			if (isSelecting)
				if (GetItemType(selectedX - 1, selectedY) != firstSelectedItemType)
				{
					if (selectedX > 0 && selectedY > 0 && GetItemType(selectedX - 1, selectedY - 1) == firstSelectedItemType)
					{
						selectedX--;
						selectedY--;
						SelectUnit(selectedX, selectedY);
					}

					else if (selectedX > 0 && selectedY > 0 && GetItemType(selectedX - 1, selectedY + 1) == firstSelectedItemType)
					{
						selectedX--;
						selectedY++;
						SelectUnit(selectedX, selectedY);
					}
					return;
				}
			selectedX--;
		}
	}
		else if (tolower(input) == 's')
		{
			if (selectedY < HEIGHT - 1)
			{
				if (isSelecting)
					if (GetItemType(selectedX, selectedY + 1) != firstSelectedItemType)
					{
						if (selectedX > 0 && selectedY > 0 && GetItemType(selectedX - 1, selectedY + 1) == firstSelectedItemType)
						{
							selectedX--;
							selectedY++;
							SelectUnit(selectedX, selectedY);
						}

						else if (selectedX > 0 && selectedY > 0 && GetItemType(selectedX + 1, selectedY + 1) == firstSelectedItemType)
						{
							selectedX++;
							selectedY++;
							SelectUnit(selectedX, selectedY);
						}
						return;
					}
				selectedY++;
				
			}
		}
		else if (tolower(input) == 'w')
		{
			if (selectedY > 0)
			{
				if (isSelecting)
					if (GetItemType(selectedX, selectedY - 1) != firstSelectedItemType)
					{
						if (selectedX > 0 && selectedY > 0 && GetItemType(selectedX - 1, selectedY - 1) == firstSelectedItemType)
						{
							selectedX--;
							selectedY--;
							SelectUnit(selectedX, selectedY);
						}

						else if (selectedX > 0 && selectedY > 0 && GetItemType(selectedX + 1, selectedY + 1) == firstSelectedItemType)
						{
							selectedX++;
							selectedY++;
							SelectUnit(selectedX, selectedY);
						}
						return;
					}
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
	isBlowing = true;

	for (auto* unit : selectedUnits)
	{
		unit->OnUnselected();
		unit->OnSelectionBlown();
		grid->FillBlanks();
		score += 10;
	}
	scoreUIDataPtr->text = "Score: " + std::to_string(score);
	isBlowing = false;
	selectedUnits.clear();  // Clear the deque
}

int UnitSelector::GetItemType(int x, int y)
{
	return grid->GetGridUnit(x, y)->UnitItem->itemType;
}
