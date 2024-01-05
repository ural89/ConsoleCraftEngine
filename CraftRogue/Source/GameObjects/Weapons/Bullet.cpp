#include "Bullet.h"

#include "Core/Scene.h"
#include "Core/ParticleSystem/ParticleSource.h"

void Bullet::Init()
{

	sprite = { 
		{1,0,1,0}, 
		{1,1,1,1}, 
		{1,0,1,0} };
	particleSource = new ParticleSource(*this);
	AddComponent(particleSource);
}

void Bullet::Update(float deltaTime)
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

void Bullet::OnCollidedBorder()
{
	Destroy();
}

void Bullet::OnCollided(const GameObject& other)
{
	
	if (other.name == "Enemy")
		Destroy();
}
