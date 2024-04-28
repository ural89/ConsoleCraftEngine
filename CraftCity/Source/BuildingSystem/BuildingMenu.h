#pragma once
#include "Core/UIHandler.h"
#include <memory>
enum class BuildingType
{
	Road = 0,
	House = 1,
	Industrial = 2

};
inline const char *ToString(BuildingType bt)
{
	switch (bt)
	{
	case BuildingType::Road:
		return "Road is selected";
	case BuildingType::House:
		return "House is selected";
	case BuildingType::Industrial:
		return "Industrial is selected";
	default:
		return "[Unknown building type]";
	}
}
class BuildingMenu
{
public:
	BuildingMenu(class UIHandler *uiHandler, class SelectCursor* selectCursor);

	void ShowBuildingPanel(bool isActive);

	BuildingType GetCurrentBuildingType() const;
	bool IsActive = false;

private:
	UIHandler *uiHandler;
	std::shared_ptr<class UIPanel> buildingPanel;
	std::shared_ptr<UIPanel> infoPanel;

	BuildingType buildingType;
	SelectCursor* selectCursor;
	
	void OnInput(int input);
	void InitPanels();
};
