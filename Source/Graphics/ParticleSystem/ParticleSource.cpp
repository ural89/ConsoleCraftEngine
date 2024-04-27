#include "ParticleSource.h"
#include "Math/Transform.h"
#include "Graphics/ParticleSystem/BlastParticle.h"
#include "Graphics/ParticleSystem/WaveParticle.h"
#include "Graphics/Scene.h"

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
		float randomAngle = static_cast<float>(rand()) / RAND_MAX * 2.0f * 3.14f;

		
		float speed = 25.0;
		float randomVelocityX = speed * std::cosf(randomAngle);
		float randomVelocityY = speed * std::sinf(randomAngle);

	
		Vector2 randomVelocity(randomVelocityX, randomVelocityY);
		//owner->GetCurrentScene().AddGameObject(new BlastParticle(owner->GetCurrentScene(), particleType, randomVelocity), owner->transform.Position + localPosition);
	}
}

void ParticleSource::EmitWaveParticle(Transform& endTransform, Vector2 localPosition)
{
	int distance = 70;
	for (int i = 0; i < distance; i++)
	{
		auto waveParticle = new
			WaveParticle(owner->GetCurrentScene(),
				 ENEMYTYPEPARTICLE,  endTransform, owner->transform, i);
		waveParticles.push_back(waveParticle);
		owner->GetCurrentScene().AddGameObject(waveParticle);
	
	}
}

void ParticleSource::ClearWaveParticles()
{
	for (auto& waveParticle : waveParticles)
	{
		waveParticle->Destroy();
	}
	waveParticles.clear();
}
