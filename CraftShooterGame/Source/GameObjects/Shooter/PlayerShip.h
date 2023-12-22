#pragma once
#include "Core/GameObject.h"
class PlayerShip : public GameObject
{
public:
	PlayerShip(class Scene& scene) : GameObject("PlayerShip", scene)
	{
		symbol = '\xDB';
		
	}
	void Init() override;
	void Update(float deltaTime) override;
};

