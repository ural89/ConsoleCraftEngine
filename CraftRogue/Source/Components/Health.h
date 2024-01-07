#pragma once
#include "Core/Component/Component.h"
class Health : public Component
{
public:
	void TakeHealth(int healthAmount);
	void AddHealth(int healthAmount);
private:
	int healthAmount;
	virtual void OnHealthDeplated();

};

