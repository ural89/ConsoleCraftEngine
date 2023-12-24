#pragma once
#include "../Core.h"
class GE_API Camera
{

public:
	void StartShake(float duration);
	void UpdateCamera(float deltaTime);

	bool isMoving = false;

	float offsetX = 0;
	float offsetY = 0; 
private:
	float xAcceleration;
	float xAccelerationStart = 3;
	bool isGoingLeft = true;
	float shakeDuration = 0.f;
};

