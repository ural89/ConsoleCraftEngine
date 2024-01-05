#include "Enemy.h"
#include "Core/Scene.h"
#include "CoreStructs/Vector.h"
void EnemyRogue::Init()
{
	sprite = {
		{4, 4, 4, 4},
		{4, 4, 4, 4},
		{4, 0, 0, 4}};
}
void EnemyRogue::Update(float deltaTime)
{
	auto player = GetCurrentScene().FindGameObject("Player");
	if(player != nullptr)
	{
		Vector2 moveDirection = player->transform.Position - transform.Position;
		moveDirection.Normalize();
		moveDirection = moveDirection * moveSpeed * deltaTime;
		transform.MovePosition(moveDirection.X, moveDirection.Y);
	}
};
