#include "Paddle.h"
#include "../Components/PlayerController.h"
void Paddle::OnKeyDown(int input)
{
	
}

void Paddle::Init()
{
	AddComponent(new PlayerController(*this, playerNo));
	sprite =  { {1,1}, {1,1} };
	
}



