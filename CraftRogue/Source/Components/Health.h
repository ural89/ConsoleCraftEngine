#pragma once
#include "Core/Component/Component.h"
class Health : public Component
{
public:
	Health(GameObject& owner) : Component(owner){}
	void GiveDamage(int healthAmount);
	void AddHealth(int healthAmount);
private:
	int healthAmount = 1;
	virtual void OnHealthDeplated();

};

