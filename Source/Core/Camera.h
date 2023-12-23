#pragma once
#include "../Core.h"
class GE_API Camera
{

public:
	void Shake(float deltaTime);

	float offsetX;
	float offsetY; 
};

