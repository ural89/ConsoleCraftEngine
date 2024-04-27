#pragma once

#include "Core/Component.h"

class GE_API PlayerController : public Component
{
public:
	PlayerController(class GameObject& go, int playerNo);
	void Init() override;
	void Update(float deltaTime) override;
	void OnKeyDown(int input);
	void RemoveListenerForInput();

private:
	int playerNo = 0;
	std::function<void(int)> inputEvent;
};

