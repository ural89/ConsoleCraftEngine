#include "BuildHandler.h"
#include "BuildingMenu.h"
#include "Core/Scene.h"
#include "CoreStructs/Vector.h"
#include "../GameObjects/Buildings/House.h"
#include "../GameObjects/Buildings/Road.h"
#include "../GameObjects/Buildings/IndustrialBuilding.h"
#include "../CityStatics/PlayerVault.h"
#include <iostream>
BuildHandler::BuildHandler(const BuildingMenu &buildingMenu, Scene &scene, PlayerVault *playerVault) : buildingMenu(buildingMenu), scene(scene), playerVault(playerVault)
{
}

void BuildHandler::Build(Vector2 position)
{
	if (buildingMenu.IsActive)
	{
		Buildable *buildable = nullptr;
		switch (buildingMenu.GetCurrentBuildingType())
		{
		case BuildingType::House:
			buildable = new House(scene);
			break;
		case BuildingType::Road:
			buildable = new Road(scene);
			break;
		case BuildingType::Industrial:
			buildable = new IndustrialBuilding(scene);
			break;
		}
		if (buildable != nullptr)
		{
			scene.AddGameObject(buildable, position);
			playerVault->SpendMoney(buildable->Price);
		}
	}
}
