#include "PlasmaBullet.h"

#include "Core/Scene.h"
#include "Core/ParticleSystem/ParticleSource.h"
#include "Core/GameObject.h"
#include "../../Components/Health.h"
void PlasmaBullet::Init()
{

	sprite = {
		{3, 3},
		{3, 3},


	};
	particleSource = new ParticleSource(*this);
	AddComponent(particleSource);
}

void PlasmaBullet::Update(float deltaTime)
{
	Vector2 movePosition = fireDirection * deltaTime * bulletSpeed;
	transform.MovePosition(movePosition.X, movePosition.Y);
	bulletSpeed += bulletAcceleration * deltaTime;
	timePassedSinceParticleSpawn += deltaTime;
	if (timePassedSinceParticleSpawn >= particleSpawnFreq)
	{
		timePassedSinceParticleSpawn = 0;
		particleSource->EmitParticle(4, FIRETYPEPARTICLE);
	}
}

void PlasmaBullet::OnCollidedBorder()
{
	Destroy();
}

void PlasmaBullet::OnCollided(GameObject &other)
{

	if (other.name == "Enemy")
	{
		other.GetComponent<Health>()->GiveDamage(damage);
		Destroy();
	}
}
