#include "PlayerController.h"
#include "Core/GameObject.h"



PlayerController::PlayerController(GameObject& go) : Component(go)
{
	
	std::cout << "owner set to " << owner->name << '\n';
}

void PlayerController::Update(float deltaTime)
{
}
