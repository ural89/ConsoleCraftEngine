#pragma once
#include "Item.h"
class ClubItem : public Item
{
public:
	ClubItem(Scene& scene) : Item(scene) {}

	void Init() override;

};

