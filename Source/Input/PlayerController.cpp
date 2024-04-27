#include "PlayerController.h"
#include "Core/GameObject.h"

#include "Input/Input.h"
#include "Graphics/Scene.h"

PlayerController::PlayerController(GameObject &go, int playerNo) : Component(go)
{
	this->playerNo = playerNo;
}

void PlayerController::Init()
{
	inputEvent = std::bind(&PlayerController::OnKeyDown, this, std::placeholders::_1);
	Input::AddListener(inputEvent);

}

void PlayerController::Update(float deltaTime)
{
}

void PlayerController::OnKeyDown(int input)
{
	if(owner)
	{
		if (!owner->GetCurrentScene().isPaused)
		{
			if (playerNo == 0)
			{
				if (tolower(Input::GetKeyDown()) == 'd')
				{
					owner->transform.MovePosition(1, 0);
				}
				if (tolower(Input::GetKeyDown()) == 'a')
				{
					owner->transform.MovePosition(-1, 0);
				}
				if (tolower(Input::GetKeyDown()) == 's')
				{
					owner->transform.MovePosition(0, 1);
				}
				if (tolower(Input::GetKeyDown()) == 'w')
				{
					owner->transform.MovePosition(0, -1);
				}
			}
			if (playerNo == 1)
			{
				if (tolower(Input::GetKeyDown()) == 'k')
				{
					owner->transform.MovePosition(1, 0);
				}
				if (tolower(Input::GetKeyDown()) == 'h')
				{
					owner->transform.MovePosition(-1, 0);
				}
				if (tolower(Input::GetKeyDown()) == 'j')
				{
					owner->transform.MovePosition(0, 1);
				}
				if (tolower(Input::GetKeyDown()) == 'u')
				{
					owner->transform.MovePosition(0, -1);
				}
			}
		}
	}
}

void PlayerController::RemoveListenerForInput()
{
	Input::RemoveListener(inputEvent);
}
