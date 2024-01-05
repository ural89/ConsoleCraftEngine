#pragma once
#include "Component.h"
#include "../../Core.h"
class GE_API PlayerController : public Component
{
public:
	PlayerController(class GameObject& go, int playerNo);
	void Init() override;
	void Update(float deltaTime) override;
	void OnKeyDown(int input);
private:
	int playerNo = 0;
};

