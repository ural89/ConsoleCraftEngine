#include "CityStatics.h"
#include "PlayerVault.h"
#include "../GameObjects/Buildings/Buildable.h"
#include <algorithm>
CityStatics::CityStatics(PlayerVault *playerVault) : playerVault(playerVault)
{
}

void CityStatics::Update(float deltaTime)
{
	timeElapsed += deltaTime;
	periodicTimePassed += deltaTime;
	if (periodicTimePassed >= periodicTime)
	{
		periodicTimePassed = 0;
		OnPeriodicTimePass();
	}
	for (auto &building : buildings)
	{
		if (building->IsDemolishFlag)
		{
			RemoveBuildable(building);
			
		}
	}
}

void CityStatics::AddBuildable(Buildable *building)
{
	buildings.push_back(building);
}

void CityStatics::RemoveBuildable(Buildable *buildable)
{
	auto it = std::find(buildings.begin(), buildings.end(), buildable);
	if (it != buildings.end())
	{
		buildings.erase(it);
	}
	buildable->Destroy();
}

void CityStatics::OnPeriodicTimePass()
{
	tickPassed += 1;

	bool hasAddedPerson = false;
	bool hasRemovedPerson = false;
	for (int i = 0; i < buildings.size(); i++)
	{
		buildings[i]->OnPeriodicTick(tickPassed);
		playerVault->EarnMoney(buildings[i]->Income);
		if (buildings[i]->AddPerson() && !hasAddedPerson)
		{
			// TODO: if total people is less than people in city
			TotalPeople++;
			hasAddedPerson = true;
		}
		// if(buildings[i]->RemovePerson() && !hasAddedPerson)
		//{
		//	//TODO: if total people is more than people in city
		//	TotalPeople--;
		//	hasRemovedPerson = true;
		// }
	}

	
}
