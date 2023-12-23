#include "Camera.h"
#include <cstdlib> 
#include <ctime>   
#include <cmath>
#include <iostream>

void Camera::StartShake(float duration)
{
    shakeDuration = duration;
    xAcceleration = xAccelerationStart;
}

void Camera::Shake(float deltaTime)
{
    xAcceleration += 20.f * deltaTime;
    if (shakeDuration > 0)
    {
        if (isGoingLeft)
        {
            offsetX += deltaTime * xAcceleration;
            offsetY -= deltaTime * xAcceleration;
            if (offsetX >= 0.2f)
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
            offsetX -= deltaTime * xAcceleration;
            offsetY += deltaTime * xAcceleration;
            if (offsetX <= -0.2f)
            {
                isGoingLeft = true;
            }
            else
            {
                //xAcceleration += 0.5f * deltaTime; 
            }
        }
        shakeDuration -= deltaTime;
    }
    else
    {
        offsetX = 0;
        offsetY = 0;
        
    }
}
