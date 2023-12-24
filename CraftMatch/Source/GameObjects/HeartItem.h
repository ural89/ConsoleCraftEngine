#pragma once
#include "Item.h"


class HeartItem : public Item
{
public:
	HeartItem(Scene& scene) : Item(scene) {}

	void Init() override;
};


