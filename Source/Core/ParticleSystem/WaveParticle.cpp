#include "WaveParticle.h"
#include "../../Core/Scene.h"
void WaveParticle::Init()
{
}

void WaveParticle::Update(float deltaTime)
{
	duration += deltaTime;
	float frequency = 1.0f;  
    float amplitude = 1.5f;  
    float speed = 15.0f;     

    Vector2 direction = endTransform->Position - startTransform->Position;
    direction.Normalize();
    direction = direction * index;

    float timeOffset = speed * duration;  

    if (index < Vector2::Distance(endTransform->Position, startTransform->Position))
    {
        float yOffset = amplitude * sin(frequency * index + timeOffset);
        transform.SetPosition(direction.X + startTransform->Position.X, direction.Y + startTransform->Position.Y + yOffset);
        isRenderable = true;
    }
    else
    {
        isRenderable = false;
    }
}
