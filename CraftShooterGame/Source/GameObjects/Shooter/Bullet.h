#pragma once
#include "Core/GameObject.h"
class Bullet : public GameObject
{
public:

	Bullet(class Scene& scene) : GameObject("Bullet", scene) 
	{
		symbol = '#';
	}
	void Init() override;
	void Update(float deltaTime) override;
	void OnCollidedBorder(int border) override;
	virtual void OnCollided(GameObject& other) override;
private:
	float bulletSpeed = 1.f;
	float bulletAcceleration = 100.f;
	float particleSpawnFreq = 0.2f;
	float timePassedSinceParticleSpawn = 0;
	class ParticleSource* particleSource;
};

