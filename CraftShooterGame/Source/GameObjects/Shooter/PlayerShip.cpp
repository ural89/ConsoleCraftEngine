#include "PlayerShip.h"
#include "../../Components/PlayerController.h"
#include "Bullet.h"
#include "Core/Input.h"
#include "Core/Scene.h"
#include "Core/EventDispatcher.h"
#include "Core/UIHandler.h"

void PlayerShip::Init()
{
	UIHandler::uiText = "Score: 0";
	AddComponent(new PlayerController(*this, 0));
	sprite = { {1,1}, {1,1,1,1},{1,1} };

	auto inputEvent = std::bind(&PlayerShip::Fire, this, std::placeholders::_1);
	Input::AddListener(inputEvent);
	
	OnEventFunction = std::bind(&PlayerShip::OnEvent, this, std::placeholders::_1);
	EventDispatcher::AddListener(OnEventFunction);

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

void PlayerShip::OnEvent(Event& event)
{
	switch (event.GetEventType())
	{
	case EventType::OnEnemyKilled:
		score++;
		UIHandler::uiText = "Score: " + std::to_string(score);
		break;
	}
	
}
