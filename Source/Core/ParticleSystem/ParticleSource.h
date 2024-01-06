#pragma once
#include "../Component/Component.h"
#include "../../Core.h"
#include "../../CoreStructs/Vector.h"
const int FIRETYPEPARTICLE = 0;
const int ENEMYTYPEPARTICLE = 1;
const int BRICKPARTICLE = 2;
struct Vector2;
class GE_API ParticleSource : public Component
{
public:
	ParticleSource(class GameObject& owner) : Component(owner){}
	void Init() override;
	void Update(float deltaTime) override;
	void EmitParticle(int count, int particleType, Vector2 localPosition =  Vector2(0,0));
	void EmitWaveParticle(Vector2 endPosition, Vector2 localPosition);
private:
	
};

