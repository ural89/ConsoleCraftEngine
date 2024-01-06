#pragma once
#include "ParticleObject.h"

class WaveParticle : public ParticleObject
{
public:
	WaveParticle(Scene& scene,  int particleType, Vector2 endPoint, 
		Transform& startTransform, 
		int index) :
		ParticleObject(scene,  particleType)
	{
		sprite = { {1,1},
					{1,1} };
		symbol = '#';
		this->startTransform = &startTransform;
		this->index = index;
		this->startPoint = startPoint;
		this->endPoint = endPoint;
	}
	void Init() override;
	void Update(float deltaTime);
private:
	Vector2 endPoint;
	Vector2 startPoint;
	Transform* startTransform;
	int index;
};

