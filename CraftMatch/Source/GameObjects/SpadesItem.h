#pragma once
#include "Item.h"

class SpadesItem : public Item
{
public:
	 SpadesItem(Scene& scene) : Item(scene) {}
	
	void Init() override;
};

