#pragma once
#include "../Core.h"
#include "../CoreStructs/Vector.h"
class GE_API Camera
{

public:
	void StartShake(float duration);
	void UpdateCamera(float deltaTime);
	void MoveCameraRight();
	void MoveCameraLeft();
	void MoveCameraUp();
	void MoveCameraDown();// for some reason moving camera with float values doesnt work
	
	bool isMoving = false;
	int HasMovedDirection = 0;
	Vector2 PreviousOffset;
	int offsetX = 0;
	int offsetY = 0;

private:
	void MoveCamera(class Vector2 moveAmount);
	void ShakeCamera(float deltaTime);
	float xAcceleration;
	float xAccelerationStart = 10;
	bool isGoingLeft = true;
	float shakeDuration = 0.f;
};
