#include "Enemy.h"
#include "Core/ParticleSystem/ParticleSource.h"
#include "Core/Scene.h"
void Enemy::Init()
{
	{

		sprite = {
			{4,4,4,4},
			{4,4,4,4},
			{4,0,0,4}
		};

	}
	particleSource = new ParticleSource(*this);
	AddComponent(particleSource);
}

void Enemy::Update(float deltaTime)
{
	transform.MovePosition(-15 * deltaTime, 0);
}

void Enemy::OnCollided(GameObject& other)
{

	if (other.name == "Bullet")
	{
		auto enemyKilledEvent = Event(EventType::OnEnemyKilled);
		EventDispatcher::CallEvent(enemyKilledEvent);
		particleSource->EmitParticle(6, ENEMYTYPEPARTICLE);
		Destroy();
	}
}

void Enemy::OnCollidedBorder(int border)
{
	Destroy();
}
