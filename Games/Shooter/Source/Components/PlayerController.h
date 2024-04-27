#pragma once

#include "Core/Component.h"

class PlayerController : public Component
{
public:
	PlayerController(class GameObject& go, int playerNo) ;
	void Init() override;
	void Update(float deltaTime) override;
	void OnKeyDown(int input);
private:
	int playerNo = 0;
};

