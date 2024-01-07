#pragma once
#include "Core/Component/Component.h"
class Health : public Component
{
public:
	Health(GameObject& owner) : Component(owner){}
	void GiveDamage(int healthAmount);
	void AddHealth(int healthAmount);
	bool HasHealthDeplated = false;
private:
	int healthAmount = 2;
	virtual void OnHealthDeplated();

};

