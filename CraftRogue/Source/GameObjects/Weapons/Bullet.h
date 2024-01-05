#pragma once
#include "Core/GameObject.h"
#include "CoreStructs/Vector.h"
class Bullet : public GameObject
{
public:

	Bullet(class Scene& scene, Vector2 fireDirection) : GameObject("Bullet", scene) 
	{
		symbol = '#';
		this->fireDirection = fireDirection;
	}
	void Init() override;
	void Update(float deltaTime) override;
	void OnCollidedBorder() override;
	virtual void OnCollided(const GameObject& other) override;
private:
	float bulletSpeed = 1.f;
	float bulletAcceleration = 100.f;
	float particleSpawnFreq = 0.2f;
	float timePassedSinceParticleSpawn = 0;
	Vector2 fireDirection = Vector2(0,0);
	class ParticleSource* particleSource;
};

