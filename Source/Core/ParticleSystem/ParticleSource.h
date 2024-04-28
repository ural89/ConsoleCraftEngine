#pragma once
#include "../Component/Component.h"
#include "../../Core.h"
#include "../../CoreStructs/Vector.h"
#include <vector>
const int FIRETYPEPARTICLE = 0;
const int ENEMYTYPEPARTICLE = 1;
const int BRICKPARTICLE = 2;
const int STATICBLASTPARTICLE = 3;
struct Vector2;
class GE_API ParticleSource : public Component
{
public:
	ParticleSource(class GameObject& owner) : Component(owner){}
	void Init() override;
	void Update(float deltaTime) override;
	void EmitParticle(int count, int particleType, Vector2 localPosition =  Vector2(0,0));
	void EmitWaveParticle(class Transform& endTransform, Vector2 localPosition);
	void ClearWaveParticles();
private:
	std::vector<class WaveParticle*> waveParticles;
	
};

