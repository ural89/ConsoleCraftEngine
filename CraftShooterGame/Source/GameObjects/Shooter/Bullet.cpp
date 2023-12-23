#include "Bullet.h"

#include "Core/Scene.h"
void Bullet::Init()
{

	sprite = { 
		{1,0,1,0}, 
		{1,1,1,1}, 
		{1,0,1,0} };
	
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
	
	if (other.name == "Enemy")
		Destroy();
}
