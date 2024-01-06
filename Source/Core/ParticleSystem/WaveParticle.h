#pragma once
#include "ParticleObject.h"

class WaveParticle : public ParticleObject
{
public:
	WaveParticle(Scene& scene,  int particleType, Transform& endTransform, 
		Transform& startTransform, 
		int index) :
		ParticleObject(scene,  particleType)
	{
		sprite = { {1,1},
					{1,1} };
		symbol = '#';
		this->startTransform = &startTransform;
		this->endTransform = &endTransform;
		this->index = index;
		
		
	}
	~WaveParticle() override
	{ 
		/*delete endTransform;
		delete startTransform;*///TODO: fix
	}
	void Init() override;
	void Update(float deltaTime);
private:
	float duration = 0;
	Transform* endTransform;
	Transform* startTransform;
	int index;
};

