#include "Bullet.h"

#include "Core/Scene.h"
#include "Core/ParticleSystem/ParticleSource.h"

void Bullet::Init()
{

	sprite = { 
		{1,0,1,0}, 
		{1,1,1,1}, 
		{1,0,1,0} };

	particleSource = new ParticleSource(GetCurrentScene());
	GetCurrentScene().AddGameObject(particleSource, transform.Position);
	particleSource->transform.SetParent(transform);
}

void Bullet::Update(float deltaTime)
{
	transform.MovePosition(bulletSpeed * deltaTime, 0);
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
