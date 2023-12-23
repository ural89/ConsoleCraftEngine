#pragma once
#include "../Core.h"
class GE_API Camera
{

public:
	void StartShake(float duration);
	void Shake(float deltaTime);

	float offsetX = 0;
	float offsetY = 0; 
private:
	float xAcceleration;
	float xAccelerationStart = 3;
	bool isGoingLeft = true;
	float shakeDuration = 0.1f;
};

