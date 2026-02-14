#include "Buildable.h"
#include "BuildingTrigger.h"
#include "../../Scenes/CraftCityScene.h"
#include "../../CityStatics/CityStatics.h"
Buildable::Buildable(Scene& scene) : GameObject("Building", scene)
{

	if (auto cityScene = static_cast<CraftCityScene*>(&scene))
	{
		cityScene->cityStatics->AddBuildable(this);
	}

}

void Buildable::Init()
{
    sprite = {{1,1} ,{1,1}};
	defaultSprite = sprite;
	for (int it = electricity; it != road; it++)
	{
		OnInfrastructureDisconnected(static_cast<InfrastructureType>(it));
	}
}

void Buildable::Update(float deltaTime)
{

}

void Buildable::OnPeriodicTick(int tickPassed)
{
	if (buildingTrigger == nullptr)
		return;

	bool hasRoadNow = buildingTrigger->HasRoad;
	bool hasElectricityNow = buildingTrigger->HasElectricity;
	bool hasWaterNow = buildingTrigger->HasWater;

	if (!HasRoad && hasRoadNow) //if has just connected road
		OnInfrastructureConnected(InfrastructureType::road);


	if (HasRoad && !hasRoadNow)
		OnInfrastructureDisconnected(InfrastructureType::road);

	if (!HasElectricity && hasElectricityNow)
		OnInfrastructureConnected(InfrastructureType::electricity);

	if (HasElectricity && !hasElectricityNow)
		OnInfrastructureDisconnected(InfrastructureType::electricity);

	HasRoad = hasRoadNow;
}
