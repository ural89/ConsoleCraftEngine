#include "Enemy.h"

void Enemy::Update(float deltaTime)
{
	transform.MovePosition(-10 * deltaTime, 0);
}
