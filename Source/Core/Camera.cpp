#include "Camera.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include "../CoreStructs/Vector.h"
void Camera::StartShake(float duration)
{
    if (isMoving)
        return;
    shakeDuration = duration;
    xAcceleration = xAccelerationStart;
    isMoving = true;
}

void Camera::UpdateCamera(float deltaTime)
{
    if (shakeDuration > 0)
        ShakeCamera(deltaTime);
}

void Camera::MoveCamera(Vector2 moveAmount)
{
    offsetX = moveAmount.X;
    offsetY = moveAmount.Y;
}

void Camera::ShakeCamera(float deltaTime)
{

    if (isGoingLeft)
    {
        offsetX = deltaTime * xAcceleration;
        offsetY = -deltaTime * xAcceleration;
        if (offsetX >= 0.01f)
        {
            isGoingLeft = false;
        }
        else
        {
            // xAcceleration += 0.5f * deltaTime;
        }
    }
    else
    {
        offsetX = -deltaTime * xAcceleration;
        offsetY = deltaTime * xAcceleration;
        if (offsetX <= -0.01f)
        {
            isGoingLeft = true;
        }
        else
        {
            // xAcceleration += 0.5f * deltaTime;
        }
    }
    shakeDuration -= deltaTime;
    if (shakeDuration <= 0)
    {
        isMoving = false;
        offsetX = 0;
        offsetY = 0;
    }
}
