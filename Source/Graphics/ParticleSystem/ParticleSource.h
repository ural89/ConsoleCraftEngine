#pragma once

#include "Core/Component.h"
#include "Math/Vector2.h"

const int FIRETYPEPARTICLE = 0;
const int ENEMYTYPEPARTICLE = 1;
const int BRICKPARTICLE = 2;

class GE_API ParticleSource : public Component
{
public:
	void Init() override;
	void Update(float deltaTime) override;
	void EmitParticle(int count, int particleType, Vector2 localPosition =  Vector2(0,0));
	void EmitWaveParticle(class Transform& endTransform, Vector2 localPosition);
	void ClearWaveParticles();

	ParticleSource(class GameObject& owner) : Component(owner) {}

private:
	std::vector<class WaveParticle*> waveParticles;	
};

