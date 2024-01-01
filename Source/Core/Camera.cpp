#include "Camera.h"
#include <cstdlib> 
#include <ctime>   
#include <cmath>
#include <iostream>

void Camera::StartShake(float duration)
{
    if (isMoving) return;
    shakeDuration = duration;
    xAcceleration = xAccelerationStart;
    isMoving = true;
}

void Camera::UpdateCamera(float deltaTime)
{
    //xAcceleration += 0.01f * deltaTime;
    if (shakeDuration > 0)
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
                //xAcceleration += 0.5f * deltaTime; 
            }
        }
        shakeDuration -= deltaTime;
    }
    else
    {
        isMoving = false;
        offsetX = 0;
        offsetY = 0;
        
    }
}
