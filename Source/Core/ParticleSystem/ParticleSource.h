#pragma once
#include "../GameObject.h"
#include "../../Core.h"
const int FIRETYPEPARTICLE = 0;
const int ENEMYTYPEPARTICLE = 1;
class GE_API ParticleSource : public GameObject
{
public:
	ParticleSource(Scene& scene) : GameObject("ParticleSource", scene){}
	void Init() override;
	void Update(float deltaTime) override;
	void EmitParticle(int count, int particleType);
private:

};

