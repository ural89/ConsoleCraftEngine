#pragma once
#include "../Core.h"
class GE_API Camera
{

public:
	void StartShake(float duration);
	void UpdateCamera(float deltaTime);
	void SetCameraSpeed(class Vector2 moveAmount);
	bool isMoving = false;

	float moveSpeedX = 0;
	float moveSpeedY = 0;

private:
	void ShakeCamera(float deltaTime);
	float xAcceleration;
	float xAccelerationStart = 10;
	bool isGoingLeft = true;
	float shakeDuration = 0.f;
};
