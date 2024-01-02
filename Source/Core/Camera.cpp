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

void Camera::SetCameraSpeed(Vector2 moveAmount)
{
    moveSpeedX = moveAmount.X;
    moveSpeedY = moveAmount.Y;
}

void Camera::ShakeCamera(float deltaTime)
{

    if (isGoingLeft)
    {
        moveSpeedX = deltaTime * xAcceleration;
        moveSpeedY = -deltaTime * xAcceleration;
        if (moveSpeedX >= 0.01f)
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
        moveSpeedX = -deltaTime * xAcceleration;
        moveSpeedY = deltaTime * xAcceleration;
        if (moveSpeedX <= -0.01f)
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
        moveSpeedX = 0;
        moveSpeedY = 0;
    }
}
