#include "ParticleSource.h"
#include "../Scene.h"
#include "BlastParticle.h"
#include "StaticBlastParticle.h"
#include "WaveParticle.h"
#include "../../CoreStructs/Transform.h"

void ParticleSource::Init()
{
}

void ParticleSource::Update(float deltaTime)
{
}

void ParticleSource::EmitParticle(int count, int particleType, Vector2 localPosition)
{
	if (particleType != STATICBLASTPARTICLE)
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
	else
	{
		owner->GetCurrentScene().AddGameObject(new StaticBlastParticle(owner->GetCurrentScene(), particleType), owner->transform.Position + localPosition);
	}
}

void ParticleSource::EmitWaveParticle(Transform &endTransform, Vector2 localPosition)
{
	int distance = 70;
	for (int i = 0; i < distance; i++)
	{
		auto waveParticle = new WaveParticle(owner->GetCurrentScene(),
											 ENEMYTYPEPARTICLE, endTransform, owner->transform, i);
		waveParticles.push_back(waveParticle);
		owner->GetCurrentScene().AddGameObject(waveParticle);
	}
}

void ParticleSource::ClearWaveParticles()
{
	for (auto &waveParticle : waveParticles)
	{
		waveParticle->Destroy();
	}
	waveParticles.clear();
}
