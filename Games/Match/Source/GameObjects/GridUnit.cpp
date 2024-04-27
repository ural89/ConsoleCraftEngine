#include "GridUnit.h"
#include "Graphics/Scene.h"

void GridUnit::Init()
{
	sprite = {  {1,1,1,1,1},
				{1,0,0,0,1},
				{1,0,0,0,1},
				{1,1,1,1,1}
	};
	overrideColor = 0;
	symbol = '\xDB';
	particleSource = new ParticleSource(*this);
	AddComponent(particleSource);
	
}

void GridUnit::OnCreatingLine()
{
	overrideColor = 4;
} 

void GridUnit::OnSelected()
{
	overrideColor = 3;
}

void GridUnit::OnUnselected()
{
	overrideColor = 0;
}

void GridUnit::OnSelectionBlown()
{
	particleSource->EmitParticle(6, ENEMYTYPEPARTICLE);
	//GetCurrentScene().camera->StartShake(0.3f);
	UnitItem->Destroy();
	UnitItem = nullptr;
}
