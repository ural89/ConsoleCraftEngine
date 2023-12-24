#pragma once
#include "Core\GameObject.h"
const int HEART = 0;
const int CLUB = 1;
const int DIAMOND = 2;
const int SPADES = 3;
class Item : public GameObject
{
public:
	Item(Scene& scene) : GameObject("Item", scene)
	{

	}
	int itemType;

	void Init() override;
	void Update(float deltaTime) override;
};

