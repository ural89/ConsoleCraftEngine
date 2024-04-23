#include "Health.h"
#include "Core/GameObject.h"
void Health::GiveDamage(float healthAmount)
{
	this->healthAmount -= healthAmount;
	
	if(this->healthAmount <= 0)
		OnHealthDeplated();
}

void Health::AddHealth(float healthAmount)
{
	this->healthAmount += healthAmount;
}

void Health::OnHealthDeplated()
{
	HasHealthDeplated = true;
	
}
