#include "Bullet.h"

void Bullet::Init()
{
	color = 1;
	sprite = { {1}, {1,1,1} , {1} };
}

void Bullet::Update(float deltaTime)
{
	transform.MovePosition(60 * deltaTime, 0);
}

void Bullet::OnCollidedBorder()
{
	Destroy();
}

void Bullet::OnCollided(const GameObject& other)
{
	if (other.name != "PlayerShip")
		Destroy();
}
