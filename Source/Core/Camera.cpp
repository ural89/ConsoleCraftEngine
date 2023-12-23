#include "Camera.h"
#include <cstdlib> 
#include <ctime>   
#include <cmath>
void Camera::Shake(float deltaTime)
{
 
    std::srand(static_cast<unsigned>(std::time(nullptr)));

  
    const float shakeIntensity = 5.0f;
    const float shakeFrequency = 10.0f;

 
    float shakeX = (std::rand() % 200 - 100) / 100.0f * shakeIntensity;
    float shakeY = (std::rand() % 200 - 100) / 100.0f * shakeIntensity;

   
    offsetX = shakeX * std::sin(shakeFrequency * deltaTime);
    offsetY = shakeY * std::cos(shakeFrequency * deltaTime);
}
