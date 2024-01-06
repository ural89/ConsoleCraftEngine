#include "ParticleSource.h"
#include "../Scene.h"
#include "BlastParticle.h"
#include "WaveParticle.h"

void ParticleSource::Init() 
{
	
	
}

void ParticleSource::Update(float deltaTime)
{
	
}

void ParticleSource::EmitParticle(int count, int particleType, Vector2 localPosition)
{
	for (int i = 0; i < count; i++)
	{
		double randomAngle = static_cast<double>(rand()) / RAND_MAX * 2 * 3.14f;

		
		double speed = 25.0; 
		double randomVelocityX = speed * std::cos(randomAngle);
		double randomVelocityY = speed * std::sin(randomAngle);

	
		Vector2 randomVelocity(randomVelocityX, randomVelocityY);
		owner->GetCurrentScene().AddGameObject(new BlastParticle(owner->GetCurrentScene(), particleType, randomVelocity), owner->transform.Position + localPosition);
	}
}

void ParticleSource::EmitWaveParticle(Vector2 endPosition, Vector2 localPosition)
{
	for (int i = 0; i < 25; i++)
	{
		owner->GetCurrentScene().AddGameObject(new
			WaveParticle(owner->GetCurrentScene(),
				 ENEMYTYPEPARTICLE,  Vector2(5, 5), (owner->transform), i));
	
	}
}
