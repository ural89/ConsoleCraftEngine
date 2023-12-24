#pragma once
#include "Core\GameObject.h"
class Item : public GameObject
{
public:
	Item(Scene& scene) : GameObject("Item", scene)
	{

	}
	void Init() override;
	void Update(float deltaTime) override;
};

