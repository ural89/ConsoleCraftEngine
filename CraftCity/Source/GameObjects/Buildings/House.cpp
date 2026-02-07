#include "House.h"
#include "BuildingTrigger.h"
#include "Core/Scene.h"
void House::Init()
{
	Buildable::Init();
	buildingTrigger = new BuildingTrigger(scene, Vector2(GetWidth() * 2, GetHeight() * 2), *this);
	scene.AddGameObject(buildingTrigger, transform.Position - Vector2(GetWidth() / 2, GetHeight() / 2));
}

void House::OnPeriodicTick(int tickPassed)
{
	Buildable::OnPeriodicTick(tickPassed);
}

void House::CalculatePotentionMaxPeople()
{
	potentialMaxPeople = 0;
	if (HasRoad)
		potentialMaxPeople += 2;
	if (HasElectricity)
		potentialMaxPeople += 2;
	if (HasWater)
		potentialMaxPeople += 2;
}
bool House::RemovePerson()
{
	if (CurrentPeople > 0)
	{
		CurrentPeople--;
		UpdateVisualForPeople();
		return true;
	}
	return false;
}
bool House::AddPerson()
{
	CalculatePotentionMaxPeople();
	if (CurrentPeople < potentialMaxPeople)
	{
		CurrentPeople++;
		UpdateVisualForPeople();
		return true;
	}
	return false;
}

void House::UpdateVisualForPeople()
{
	int people = CurrentPeople;
	people = std::max(0, people);
	for (int i = 0; i < sprite.size(); ++i)
	{ // Clear people
		for (int j = 0; j < sprite[i].size(); ++j)
		{
			if (!(i == 0 || j == sprite[i].size() - 1 || j == 0 || i == sprite.size() - 1))
			{
				sprite[i][j] = 0;
			}
		}
	}
	transform.HasClearedFlag = false;
	transform.HasMovedThisFrame = true;
	for (int i = 0; i < sprite.size(); ++i)
	{
		for (int j = 0; j < sprite[i].size(); ++j)
		{
			if (!(i == 0 || j == sprite[i].size() - 1 || j == 0 || i == sprite.size() - 1))
			{
				if (people == 0)
				{

					break;
				}
				sprite[i][j] = YELLOW;
				people--;
			}
		}
	}
}

void House::OnInfrastructureDisconnected(InfrastructureType infraStructureType)
{
	sprite = {
		{RED, RED, RED, RED},
		{RED, 0, 0, RED},
		{RED, 0, 0, RED},
		{RED, 0, 0, RED},
		{RED, RED, RED, RED}};
}

void House::OnInfrastructureConnected(InfrastructureType infraStructureType)
{
	sprite = defaultSprite;
}
