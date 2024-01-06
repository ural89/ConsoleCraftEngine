#include "WaveParticle.h"
#include "../../Core/Scene.h"
void WaveParticle::Init()
{
	
}

void WaveParticle::Update(float deltaTime)
{
	duration += deltaTime;
	if (duration > 1)
	{
//		GetCurrentScene().isPaused = true;
		Destroy();
		return;
	}
	Vector2 direction =  endTransform->Position - startTransform->Position;
	direction.Normalize();
	direction = direction * index;
	
	if (index < Vector2::Distance(endTransform->Position, startTransform->Position))
	{
		transform.SetPosition(direction.X + startTransform->Position.X, direction.Y + startTransform->Position.Y);
		isRenderable = true;
	}
	else
		isRenderable = false;
}
