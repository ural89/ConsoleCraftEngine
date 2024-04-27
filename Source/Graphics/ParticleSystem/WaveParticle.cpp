#include "WaveParticle.h"
#include "Graphics/Scene.h"

void WaveParticle::Init()
{
}

void WaveParticle::Update(float deltaTime)
{
	duration += deltaTime;
    //speed += deltaTime * 10; 
    speed += 4 * deltaTime;
   // amplitude -= deltaTime / 2 ;
    Vector2 direction = endTransform->Position - startTransform->Position;
    direction.Normalize();
    direction = direction * static_cast<float>(index);

    float timeOffset = speed * duration;  

    if (index < Vector2::Distance(endTransform->Position, startTransform->Position))
    {
        float yOffset = amplitude * sin(frequency * index + timeOffset);
        transform.SetPosition(direction.X + startTransform->Position.X + 2, direction.Y + startTransform->Position.Y + yOffset + 2);
        isRenderable = true;
    }
    else
    {
        isRenderable = false;
    }
}
