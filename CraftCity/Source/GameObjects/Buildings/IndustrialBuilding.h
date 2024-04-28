#pragma once
#include "Buildable.h"
class IndustrialBuilding : public Buildable
{
public:
	IndustrialBuilding(class Scene& scene) : Buildable(scene)
	{
		name = "Industrial";
		sprite = {
		  {GREEN, GREEN, GREEN, GREEN},
		  {GREEN, 0, 0, GREEN},
		  {GREEN, 0, 0, GREEN},
		  {GREEN, GREEN, GREEN, GREEN} };
		symbol = 'X';

		Price = 30;
		Income = 0;
	}
	void Init() override;
	void OnInfrastructureConnected(InfrastructureType) override;
	void OnInfrastructureDisconnected(InfrastructureType) override;
	void OnPeriodicTick(int tickPassed) override;
private:
	void CalculateIncome();

};

