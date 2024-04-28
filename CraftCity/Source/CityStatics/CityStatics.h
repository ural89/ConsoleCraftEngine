#pragma once
#include <vector>
class CityStatics
{
public:
	CityStatics(class PlayerVault* playerVault);
	int AverageRating = 0;
	int TotalIncome = 0;
	int TotalPeople = 0;
	
	void Update(float deltaTime);
	void AddBuildable(class Buildable* buildable);
	void RemoveBuildable(Buildable* buildable);
private:
	std::vector<Buildable*> buildings;
	PlayerVault* playerVault;

	void OnPeriodicTimePass();
	int tickPassed = 0;
	double timeElapsed = 0;
	float periodicTime = 1;
	float periodicTimePassed = 0;

	int houseCount = 0;
	int industrialCount = 0;
};

