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
		Sprite sprite = { {10} };
        SetSprite(sprite);
		symbol = '=';
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

	float frequency = 0.2f;
	float amplitude = 2.f;
	float speed = 15.0f;

	Transform* endTransform;
	Transform* startTransform;
	int index;
};

