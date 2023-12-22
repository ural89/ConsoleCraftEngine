#include "PlayerShip.h"
#include "../../Components/PlayerController.h"
void PlayerShip::Init()
{
	AddComponent(new PlayerController(*this, 0));
	sprite = { {1}, {1} };
}

void PlayerShip::Update(float deltaTime)
{
	
}
