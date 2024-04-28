#include "BuildingMenu.h"
#include "Core/Input.h"
#include "../GameObjects/SelectCursor.h"
#include <iostream>
BuildingMenu::BuildingMenu(UIHandler *uiHandler, SelectCursor *selectCursor) : uiHandler(uiHandler), selectCursor(selectCursor)
{
	auto keyEvent = BIND_EVENT_FN(BuildingMenu::OnInput);
	Input::AddListener(keyEvent);
	InitPanels();
	ShowBuildingPanel(false);
}

void BuildingMenu::ShowBuildingPanel(bool isActive)
{
	IsActive = isActive;
	buildingPanel->SetActive(isActive);
	if (!isActive)
	{
		infoPanel->SetActive(true);
		infoPanel->ChangeText(0, "b to open building menu");
	}
	
}

BuildingType BuildingMenu::GetCurrentBuildingType() const
{
	return buildingType;
}

void BuildingMenu::OnInput(int input)
{
	switch (input)
	{
	case 'b':
		ShowBuildingPanel(!buildingPanel->isActive);
		infoPanel->ChangeText(0, "Select building type");
		break;

	case '1':
		if (buildingPanel->isActive)
		{
			buildingType = BuildingType::Road;
			selectCursor->SetSize(Vector2(2, 2), '=');
			infoPanel->ChangeText(0, ToString(buildingType));
			break;
		}
	case '2':

		if (buildingPanel->isActive)
		{
			buildingType = BuildingType::House;
			selectCursor->SetSize(Vector2(4, 5), '#');
			infoPanel->ChangeText(0, ToString(buildingType));
			break;
		}
	case '3':

		if (buildingPanel->isActive)
		{
			buildingType = BuildingType::Industrial;
			selectCursor->SetSize(Vector2(4, 4), 'X');
			infoPanel->ChangeText(0, ToString(buildingType));
			break;
		}
	}
}

void BuildingMenu::InitPanels()
{
	// info panel
	infoPanel = std::make_shared<UIPanel>();
	infoPanel->AddString(Vector2(SCREENWIDTH / 2, SCREENHEIGHT - 5), "");
	// building panel
	buildingPanel = std::make_shared<UIPanel>();
	buildingPanel->isActive = false;
	buildingPanel->AddString(Vector2(15, SCREENHEIGHT - 5), "1. = Road");
	buildingPanel->AddString(Vector2(15, SCREENHEIGHT - 4), "2. # House");
	buildingPanel->AddString(Vector2(15, SCREENHEIGHT - 3), "3. @ Electricity");
	if (uiHandler != nullptr)
	{
		uiHandler->AddPanel(buildingPanel);
		uiHandler->AddPanel(infoPanel);
	}
}
