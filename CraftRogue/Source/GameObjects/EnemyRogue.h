#pragma once
#include "Core/GameObject.h"
class EnemyRogue : public GameObject
{
public:

	EnemyRogue(class Scene& scene) : GameObject("Enemy", scene) 
	{
		symbol = '#';
	}
	~EnemyRogue();
	void Init() override;
	void Update(float deltaTime) override;

protected:
	float moveSpeed = 5;
	int health = 2;
private:
	class ParticleSource* particleSource;
};

