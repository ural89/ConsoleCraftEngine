#include "EnemyRogue.h"

#include "Graphics/Scene.h"
#include "Math/Vector2.h"
#include "Graphics/ParticleSystem/ParticleSource.h"
#include "Event/Event.h"
#include "Event/EventDispatcher.h"

#include "Components/Health.h"

EnemyRogue::~EnemyRogue()
{
	
}
void EnemyRogue::Init()
{
	
	sprite = {
		{4, 4, 4, 4},
		{4, 1, 1, 4},
		{4, 0, 0, 4}};
	particleSource = new ParticleSource(*this);
	AddComponent(particleSource);
	AddComponent(new Health(*this));
}
void EnemyRogue::Update(float deltaTime)
{
	if (GetComponent<Health>()->HasHealthDeplated && !isDead)
	{
		OnDie();
		return;
	}
	MoveToPlayer(deltaTime);
	elapsedTime += deltaTime;
	if (elapsedTime >= 0.2f)
	{
		OnMove();
		elapsedTime = 0;
	}
}
void EnemyRogue::OnDie()
{
	isDead = true;
	particleSource->EmitParticle(4, ENEMYTYPEPARTICLE);
	Event enemyKilledEvent = Event(EventType::OnEnemyKilled);
	EventDispatcher::CallEvent(enemyKilledEvent);
	Destroy();
}
void EnemyRogue::MoveToPlayer(float deltaTime)
{
	auto player = GetCurrentScene().FindGameObject("Player");
	if (player != nullptr)
	{
		Vector2 moveDirection = player->transform.Position - transform.Position;
		moveDirection.Normalize();
		moveDirection = moveDirection * moveSpeed * deltaTime;
		transform.MovePosition(moveDirection.X, moveDirection.Y);
	}
}
void EnemyRogue::OnMove()
{
	
};
