#include "EnemyRogue.h"

#include "Core/Scene.h"
#include "CoreStructs/Vector.h"
#include "Core/ParticleSystem/ParticleSource.h"
#include "Core/Event.h"
#include "Core/EventDispatcher.h"

#include "../Components/Health.h"
EnemyRogue::~EnemyRogue()
{
	particleSource->EmitParticle(4, ENEMYTYPEPARTICLE);
	Event enemyKilledEvent = Event(EventType::OnEnemyKilled);
	EventDispatcher::CallEvent(enemyKilledEvent);
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
	auto player = GetCurrentScene().FindGameObject("Player");
	if (player != nullptr)
	{
		Vector2 moveDirection = player->transform.Position - transform.Position;
		moveDirection.Normalize();
		moveDirection = moveDirection * moveSpeed * deltaTime;
		transform.MovePosition(moveDirection.X, moveDirection.Y);
	}
};


