#include "Paddle.h"
#include "../Components/PlayerController.h"
void Paddle::OnKeyDown(int input)
{
	if(playerNo == 0)
	{
		if (tolower(Input::GetKeyDown()) == 'd')
		{
			transform.MovePosition(1, 0);
		}
		if (tolower(Input::GetKeyDown()) == 'a')
		{
			transform.MovePosition(-1, 0);
		}
		if (tolower(Input::GetKeyDown()) == 's')
		{
			transform.MovePosition(0, 1);
		}
		if (tolower(Input::GetKeyDown()) == 'w')
		{
			transform.MovePosition(0, -1);

		}
	}
	if (playerNo == 1)
	{
		if (tolower(Input::GetKeyDown()) == 'k')
		{
			transform.MovePosition(1, 0);
		}
		if (tolower(Input::GetKeyDown()) == 'h')
		{
			transform.MovePosition(-1, 0);
		}
		if (tolower(Input::GetKeyDown()) == 'j')
		{
			transform.MovePosition(0, 1);
		}
		if (tolower(Input::GetKeyDown()) == 'u')
		{
			transform.MovePosition(0, -1);

		}
		
	}
}

void Paddle::Init()
{
	AddComponent(new PlayerController(*this));
	sprite =  { {1,1}, {1,1} };
	auto event = std::bind(&Paddle::OnKeyDown, this, std::placeholders::_1);
	Input::AddListener(event);
}



