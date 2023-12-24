#pragma once
#include "Item.h"

class DiamondItem : public Item
{
public:
	DiamondItem(Scene& scene) : Item(scene) {}

	void Init() override;
};

