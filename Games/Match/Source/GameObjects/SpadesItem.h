#pragma once

#include "Item.h"

class SpadesItem : public Item
{
public:
	SpadesItem(Scene& scene) : Item(scene) {
		itemType = SPADES;
	}
	
	void Init() override;
};

