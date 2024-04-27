#include "ParticleObject.h"
#include "Math/Vector2.h"

ParticleObject::ParticleObject(Scene& scene, int particleType) : GameObject("Particle", scene)
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
	}
	symbol = '#';
}

void ParticleObject::Init()
{
	lastPosition = transform.Position.ToInt();
	

}

void ParticleObject::Update(float deltaTime)
{
	
}

void ParticleObject::OnCollidedBorder()
{
	
}

