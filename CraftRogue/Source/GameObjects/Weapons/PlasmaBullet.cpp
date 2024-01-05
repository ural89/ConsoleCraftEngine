#include "PlasmaBullet.h"

#include "Core/Scene.h"
#include "Core/ParticleSystem/ParticleSource.h"

void PlasmaBullet::Init()
{

	sprite = {
		{2,2}, 
		{2,2}, 
		
		// {0,2,0}, 
		// {2,3,2}, 
		// {0,2,0} 
		};
	particleSource = new ParticleSource(*this);
	AddComponent(particleSource);
}

void PlasmaBullet::Update(float deltaTime)
{
	Vector2 movePosition =  fireDirection * deltaTime * bulletSpeed;
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

void PlasmaBullet::OnCollided(const GameObject& other)
{
	
	if (other.name == "Enemy")
		Destroy();
}
