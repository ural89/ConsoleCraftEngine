#include "StaticBlastParticle.h"

void StaticBlastParticle::Update(float deltaTime)
{
    elapsedTime += deltaTime;
    if (elapsedTime > duration)
    {
        Destroy();
    }
    if (elapsedTime > stage03Time)
    {
        Sprite sprite = {
            {1, 1},
            {1, 1}};
        SetSprite(sprite);
    }
    else if (elapsedTime > stage02Time)
    {
        Sprite sprite = {
            {1},
            {1}};
        SetSprite(sprite);
    }
    else if (elapsedTime > stage01Time)
    {
        Sprite sprite = {
            {1}

        };
        SetSprite(sprite);
    }
}

void StaticBlastParticle::OnCollidedBorder(int border)
{
    Destroy();
}
