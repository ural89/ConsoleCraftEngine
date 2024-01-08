#pragma once
#include "Core/GameObject.h"
#include "CoreStructs/Vector.h"
class PlasmaBullet : public GameObject
{
public:
	PlasmaBullet(class Scene &scene, Vector2 fireDirection, float damage) : GameObject("Bullet", scene)
	{
		sprite = {
			{3, 3},
			{3, 3}
		};
		symbol = '#';
		this->fireDirection = fireDirection;
		this->damage = damage;
	}
	void Init() override;
	void Update(float deltaTime) override;
	void OnCollidedBorder() override;
	virtual void OnCollided(GameObject &other) override;

private:
	float bulletSpeed = 1.f;
	float bulletAcceleration = 100.f;
	float particleSpawnFreq = 0.2f;
	float timePassedSinceParticleSpawn = 0;
	Vector2 fireDirection = Vector2(0, 0);
	class ParticleSource *particleSource;
	float damage;
};
