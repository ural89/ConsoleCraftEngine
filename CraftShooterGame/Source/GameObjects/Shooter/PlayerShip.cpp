#include "PlayerShip.h"
#include "../../Components/PlayerController.h"
#include "Bullet.h"
#include "Core/Input.h"
#include "Core/Scene.h"
void PlayerShip::Init()
{
	AddComponent(new PlayerController(*this, 0));
	sprite = { {1,1}, {1,1,1,1},{1,1} };

	auto event = std::bind(&PlayerShip::Fire, this, std::placeholders::_1);
	Input::AddListener(event);
}

void PlayerShip::Update(float deltaTime)
{
	
}

void PlayerShip::Fire(int keyDown)
{
	if (keyDown == SPACEBAR)
	{
		GetCurrentScene().AddGameObject(new Bullet(GetCurrentScene()), transform.Position);
	}
}
