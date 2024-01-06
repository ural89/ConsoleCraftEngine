#include "BlastParticle.h"

void BlastParticle::Update(float deltaTime)
{
	transform.MovePosition(velocity.X * deltaTime, velocity.Y * deltaTime);
	velocity.Y += gravity * deltaTime;

	if (lastPosition != transform.Position.ToInt())
	{
		lastPosition = transform.Position.ToInt();
		trailPositions[trailCount] = lastPosition;
		//GetCurrentScene(todo particle trail).AddGameObject()
	}
}
