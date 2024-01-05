#include "EnemyRogue.h"
#include "Core/Scene.h"
#include "CoreStructs/Vector.h"
#include "EnemyRogue.h"
#include "Core/ParticleSystem/ParticleSource.h"
void EnemyRogue::Init()
{
	sprite = {
		{4, 4, 4, 4},
		{4, 4, 4, 4},
		{4, 0, 0, 4}};
	particleSource = new ParticleSource(*this);
	AddComponent(particleSource);
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
void EnemyRogue::OnCollided(const GameObject &other)
{
	if (other.name == "Bullet")
	{
		particleSource->EmitParticle(4, ENEMYTYPEPARTICLE);
		Destroy();
	}
}
