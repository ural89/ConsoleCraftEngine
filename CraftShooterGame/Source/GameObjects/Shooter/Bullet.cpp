#include "Bullet.h"

void Bullet::Init()
{
	sprite = { {1}, {1,1,1} , {1} };
}

void Bullet::Update(float deltaTime)
{
	transform.MovePosition(30 * deltaTime, 0);
}

void Bullet::OnCollidedBorder()
{
	Destroy();
}
