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
        sprite = {
            {1, 1},
            {1, 1}};
    }
    else if (elapsedTime > stage02Time)
    {
        sprite = {
            {1},
            {1}};
    }
    else if (elapsedTime > stage01Time)
    {
        sprite = {
            {1}

        };
    }
}

void StaticBlastParticle::OnCollidedBorder(int border)
{
    Destroy();
}
