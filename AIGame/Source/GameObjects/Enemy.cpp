#include "Enemy.h"
#include "Core/Component/AI/AIMovement.h"
#include "Core/ParticleSystem/ParticleSource.h"
#include "Core/Scene.h"
void Enemy::Init()
{
	{

		Sprite sprite = {
			{4, 4, 4, 4},
			{4, 4, 4, 4},
			{4, 0, 0, 4}};
        SetSprite(sprite);
	}
	particleSource = new ParticleSource(*this);
	auto aiMovement = new AIMovement(*this);
	AddComponent(particleSource);
	AddComponent(aiMovement);
	aiMovement->SetTargetTransform(&GetCurrentScene().FindGameObject("PlayerShip")->transform);
	isNavIgnore = true;
	transform.Size = Vector2(4, 4);
}

void Enemy::Update(float deltaTime)
{
	// transform.MovePosition(-1 * deltaTime, 0);
}

void Enemy::OnCollided(GameObject &other)
{

	if (other.name == "Bullet")
	{
		// auto enemyKilledEvent = Event(EventType::OnEnemyKilled);
		// EventDispatcher::CallEvent(enemyKilledEvent);
		// particleSource->EmitParticle(6, ENEMYTYPEPARTICLE);
		// Destroy();
	}
}

void Enemy::OnCollidedBorder(int border)
{
	// Destroy();
}
