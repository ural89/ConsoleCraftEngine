#include "ParticleObject.h"
#include "../../CoreStructs/Vector.h"

ParticleObject::ParticleObject(Scene &scene, int particleType) : GameObject("Particle", scene)
{

	switch (particleType)
	{
	case 0:
		sprite = fireParticle;
		break;
	case 1:
		sprite = enemyParticle;
		break;
	case 2:
		sprite = brickParticle;
		break;
	case 3:
		sprite = fireParticle;
		break;
	}
	SetSprite(sprite);
	symbol = '#';
}

void ParticleObject::Init()
{
	lastPosition = transform.Position.ToInt();
}

void ParticleObject::Update(float deltaTime)
{
}

void ParticleObject::OnCollidedBorder(int border)
{
}
