#pragma once
#include "ParticleObject.h"
#include "../../Core.h"
class GE_API StaticBlastParticle : public ParticleObject
{
public:
	StaticBlastParticle(Scene& scene, int particleType) :
		ParticleObject(scene,  particleType) {
		
	};
	void Update(float deltaTime) override;
	void OnCollidedBorder(int border) override;
private:
    float duration = 0.3;
	float elapsedTime = 0;
	float stage01Time = 0.0f;
	float stage02Time = 0.1f;
	float stage03Time = 0.2f;
};

