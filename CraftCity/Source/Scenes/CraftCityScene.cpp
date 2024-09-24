#include "CraftCityScene.h"
#include "../GameObjects/SelectCursor.h"
#include "../GameObjects/Buildings/Road.h"
#include "Core/Input.h"
#include "Core/UIHandler.h"
#include "../BuildingSystem/BuildingMenu.h"
#include "../BuildingSystem/BuildHandler.h"
#include "../BuildingSystem/DemolishHandler.h"
#include "../CityStatics/CityStatics.h"
#include "../CityStatics/PlayerVault.h"
#include "../UI/PlayerStatsUI.h"
CraftCityScene::~CraftCityScene()
{

	delete buildHandler;
	delete buildMenu;
	delete playerVault;
	delete playerStatsUI;
	delete cityStatics;
	delete demolishHandler;
}
void CraftCityScene::Init()
{
	playerVault = new PlayerVault();
	cityStatics = new CityStatics(playerVault);
	selectCursor = new SelectCursor(*this);
	buildMenu = new BuildingMenu(uiHandler, selectCursor);
	buildHandler = new BuildHandler(*buildMenu, *this, playerVault);
	playerStatsUI = new PlayerStatsUI(uiHandler, playerVault, cityStatics);
	demolishHandler = new DemolishHandler(*cityStatics);

	auto keyEvent = BIND_EVENT_FN(CraftCityScene::OnInput);
	Input::AddListener(keyEvent);

	AddGameObject(selectCursor, Vector2(SCREENWIDTH / 2, SCREENHEIGHT / 2));

	auto mainRoad = new Road(*this);
	mainRoad->IsMainRoad = true;
	mainRoad->HasConnectedToMain = true;
	mainRoad->overrideColor = 2;
	AddGameObject(mainRoad, Vector2(SCREENWIDTH / 2 + 2, SCREENHEIGHT / 2 + 2));
}

void CraftCityScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);
	playerStatsUI->Update(deltaTime);
	cityStatics->Update(deltaTime);
}

void CraftCityScene::OnInput(int input)
{
	float cameraMoveSpeed = 1;

	if (std::tolower(input) == 'd')
	{
		selectCursor->transform.MovePosition(cameraMoveSpeed, 0);
		camera->MoveCameraLeft();
	}
	if (std::tolower(input) == 'a')
	{
		selectCursor->transform.MovePosition(-cameraMoveSpeed, 0);
		camera->MoveCameraRight();
	}
	if (std::tolower(input) == 'w')
	{
		selectCursor->transform.MovePosition(0, -cameraMoveSpeed);
		camera->MoveCameraUp();
	}
	if (std::tolower(input) == 's')
	{
		selectCursor->transform.MovePosition(0, cameraMoveSpeed);
		camera->MoveCameraDown();
	}
	if (std::tolower(input) == 'e' && selectCursor->CanBuild)
	{

		buildHandler->Build(selectCursor->transform.Position);
	}
	if (std::tolower(input) == 'f')
	{
		if (auto collidedObject = selectCursor->GetCollidedObject())
		{
			demolishHandler->Demolish(*collidedObject);
			selectCursor->ResetCollidedObject();
		}
	}
}
