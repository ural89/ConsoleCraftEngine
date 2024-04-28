#pragma once
#include "Buildable.h"
class Road : public Buildable
{
public:
	Road(class Scene& scene) : Buildable(scene)
	{
		name = "Road";
		sprite = { {1,1}, 
			{1,1} };
	
	}
	bool IsMainRoad = false;
	bool HasConnectedToMain = false;
	void Init() override;
	void OnInfrastructureConnected(InfrastructureType infrastructureType) override;
	void OnInfrastructureDisconnected(InfrastructureType infrastructureType) override;

private:
};

