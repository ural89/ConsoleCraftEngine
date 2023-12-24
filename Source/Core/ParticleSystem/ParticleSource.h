#pragma once
#include "../Component/Component.h"
#include "../../Core.h"
const int FIRETYPEPARTICLE = 0;
const int ENEMYTYPEPARTICLE = 1;
class GE_API ParticleSource : public Component
{
public:
	ParticleSource(class GameObject& owner) : Component(owner){}
	void Init() override;
	void Update(float deltaTime) override;
	void EmitParticle(int count, int particleType);
private:

};

