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
	void OnCollided(const GameObject& other) override;

protected:
	float moveSpeed = 5;
	int health = 1;
private:
	class ParticleSource* particleSource;
};

