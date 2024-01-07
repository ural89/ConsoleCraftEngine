#include "Health.h"
#include "Core/GameObject.h"
void Health::GiveDamage(int healthAmount)
{
	this->healthAmount -= healthAmount;
	
	if(this->healthAmount <= 0)
		OnHealthDeplated();
}

void Health::AddHealth(int healthAmount)
{
	this->healthAmount -= healthAmount;
}

void Health::OnHealthDeplated()
{
	HasHealthDeplated = true;
	
}
