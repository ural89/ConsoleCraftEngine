#include "ParticleObject.h"
#include "../../CoreStructs/Vector.h"

ParticleObject::ParticleObject(Scene& scene, Vector2 startVelocity, int particleType) : GameObject("Particle", scene)
{
	this->velocity = startVelocity;
	switch (particleType)
	{
	case 0:
		sprite = sprite01;
		break;
	case 1:
		sprite = sprite02;
		break;
	}
	symbol = '#';
}

void ParticleObject::Init()
{
	lastPosition = transform.Position.ToInt();
	

}

void ParticleObject::Update(float deltaTime)
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

void ParticleObject::OnCollidedBorder()
{
	Destroy();
}

