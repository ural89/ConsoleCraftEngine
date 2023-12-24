#include "PlayerShip.h"
#include "../../Components/PlayerController.h"
#include "Bullet.h"
#include "Core/Input.h"
#include "Core/Scene.h"
#include "Core/EventDispatcher.h"
#include "Core/UIHandler.h"
#include "Core/ParticleSystem/ParticleSource.h"

void PlayerShip::Init()
{
	UIHandler::uiText = "Score: 0";

	AddComponent(new PlayerController(*this, 0));
	sprite = 
	{
		{2,2,0,2},
		{1,1,1,1},
		{1,1,1,1},
		{2,2,0,2}
	};
	auto inputEvent = std::bind(&PlayerShip::Fire, this, std::placeholders::_1);
	Input::AddListener(inputEvent);
	
	OnEventFunction = std::bind(&PlayerShip::OnEvent, this, std::placeholders::_1);
	EventDispatcher::AddListener(OnEventFunction);
	
	particleSource = new ParticleSource(*this);
	AddComponent(particleSource);
}

void PlayerShip::Update(float deltaTime)
{
	
}

void PlayerShip::OnCollided(const GameObject& other)
{
	if (other.name == "Enemy")
	{
		std::cout << "GAME OVER!" << '\n';
		GetCurrentScene().hasGameOver = true;
	}
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
		GetCurrentScene().camera->StartShake(0.25f);
		UIHandler::uiText = "Score: " + std::to_string(score);
		break;
	}
	
}
