#pragma once
#include "Core/GameObject.h"

enum InfrastructureType
{
	electricity,
	water,
	road
};
class Buildable : public GameObject
{
  public:
	Buildable(class Scene &scene);
	void Init() override;
	void Update(float deltaTime) override;
	virtual bool AddPerson()
	{
		return false;
	};
	virtual bool RemovePerson()
	{
		return false;
	};
	virtual void OnPeriodicTick(int tickPassed);

	int Rating = 0;
	int Income = 0;
	int MaxPeople = 0;
	int CurrentPeople = 0;
	int Price = 10;
	int PeriodicCost = 1;

	bool HasElectricity = false;
	bool HasRoad = false;
	bool HasWater = false;
	bool HasWastePipe = false;

	bool IsDemolishFlag = false;

  private:
	float elapsedTime = 0;

  protected:
	virtual void OnInfrastructureConnected(InfrastructureType infrastructureType)
	{
	}
	virtual void OnInfrastructureDisconnected(InfrastructureType infrastructureType)
	{
	}

	Sprite defaultSprite;
	Sprite sprite;
	int progress = 0;
	class BuildingTrigger *buildingTrigger = nullptr;
};
