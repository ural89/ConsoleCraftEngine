#pragma once
#include "Core/GameObject.h"
class EnemyRogue : public GameObject
{
public:
	EnemyRogue(class Scene &scene) : GameObject("Enemy", scene)
	{
		symbol = '#';
	}
	~EnemyRogue();
	void Init() override;
	void Update(float deltaTime) override;


	void MoveToPlayer(float deltaTime);


protected:
	float moveSpeed = 5;
	int health = 2;

	bool isDead = false;
	
	virtual void OnDie();
	virtual void OnMove();

private:
	float elapsedTime = 0;
	class ParticleSource *particleSource;
};
