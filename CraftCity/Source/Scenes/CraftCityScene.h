#pragma once
#include "Core/Scene.h"
class CraftCityScene : public Scene
{
public:
	~CraftCityScene();
	
	void Init() override;
	void Update(float deltaTime) override;

	class CityStatics* cityStatics;
private:

	void OnInput(int input);
	Vector2 cameraOffset;
	class PlayerVault* playerVault;
	class BuildingMenu* buildMenu;
	class BuildHandler* buildHandler;
	class SelectCursor* selectCursor;
	class PlayerStatsUI* playerStatsUI;
	class DemolishHandler* demolishHandler;

};

