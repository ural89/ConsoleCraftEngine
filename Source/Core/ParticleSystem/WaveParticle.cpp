#include "WaveParticle.h"

void WaveParticle::Init()
{

	
	
}

void WaveParticle::Update(float deltaTime)
{
	Vector2 direction =  startTransform->Position;
	direction.Normalize();
	//std::cout << direction.X << " " << direction.Y << '\n';
	transform.Position = direction * index;
}
