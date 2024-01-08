#pragma once
#include "Core/Component/Component.h"
class Health : public Component
{
public:
	Health(GameObject& owner) : Component(owner){}
	void GiveDamage(float healthAmount);
	void AddHealth(float healthAmount);
	bool HasHealthDeplated = false;
private:
	float healthAmount = 1;
	virtual void OnHealthDeplated();

};

