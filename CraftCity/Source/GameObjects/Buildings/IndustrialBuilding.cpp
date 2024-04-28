#include "IndustrialBuilding.h"
#include "BuildingTrigger.h"
#include "Core/Scene.h"
void IndustrialBuilding::Init()
{
	Buildable::Init();
	buildingTrigger = new BuildingTrigger(scene, Vector2(GetWidth() * 2, GetHeight() * 2), *this);
	scene.AddGameObject(buildingTrigger, transform.Position - Vector2(GetWidth() / 2, GetHeight() / 2));
}

void IndustrialBuilding::OnInfrastructureConnected(InfrastructureType)
{
	overrideColor = GREEN;
}

void IndustrialBuilding::OnInfrastructureDisconnected(InfrastructureType)
{
	overrideColor = RED;
}

void IndustrialBuilding::OnPeriodicTick(int tickPassed)
{
	Buildable::OnPeriodicTick(tickPassed);
}

void IndustrialBuilding::CalculateIncome()
{
	Income = 0;
	if (HasRoad)
	{
		Income += 5;
	}
	if (HasElectricity)
	{
		Income += 5;
	}
}
