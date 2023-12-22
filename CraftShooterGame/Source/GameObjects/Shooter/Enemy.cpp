#include "Enemy.h"

void Enemy::Update(float deltaTime)
{
	transform.MovePosition(-10 * deltaTime, 0);
}

void Enemy::OnCollided(const GameObject& other)
{

	if(other.name == "Bullet")
		Destroy();
}

void Enemy::OnCollidedBorder()
{
	Destroy();
}
