#pragma once
#include "Core/Component/Component.h"
class PlayerController : public Component
{
public:
	PlayerController(class GameObject& go) ;
	void Init() override {};
	void Update(float deltaTime) override;
};

