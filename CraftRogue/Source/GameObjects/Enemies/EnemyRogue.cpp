#include "EnemyRogue.h"

#include "Core/Scene.h"
#include "CoreStructs/Vector.h"
#include "Core/ParticleSystem/ParticleSource.h"
#include "Core/Event.h"
#include "Core/EventDispatcher.h"

#include "../../Components/Health.h"
EnemyRogue::~EnemyRogue()
{

}
void EnemyRogue::Init()
{

	sprite = {
		{4, 4, 4, 4},
		{4, 1, 1, 4},
		{4, 0, 0, 4}};
    SetSprite(sprite);
	particleSource = AddComponent<ParticleSource>();
	AddComponent<Health>();
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
