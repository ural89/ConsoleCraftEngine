#include "Ball.h"

void Ball::Update(float deltaTime)
{
	{
		transform.MovePosition(velocity.X * deltaTime, velocity.Y * deltaTime);
		if (transform.Position.X >= SCREENWIDTH - 1 || transform.Position.X <= 1)
		{
			velocity.X *= -1;
		}
		if (transform.Position.Y >= SCREENHEIGHT - 3 || transform.Position.Y <= 1)
		{
			velocity.Y *= -1;
		}

	}
}

void Ball::OnCollided(GameObject& other)
{
	Destroy();
	velocity.X *= -1;
	velocity.Y *= -1;
}
