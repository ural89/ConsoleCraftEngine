#pragma once
#include "Core/GameObject.h"
class EnemyRogue : public GameObject
{
public:

	EnemyRogue(class Scene& scene) : GameObject("Enemy", scene) 
	{
		symbol = '#';
	}
	void Init() override;
	void Update(float deltaTime) override;
private:
	float moveSpeed = 5;
};

