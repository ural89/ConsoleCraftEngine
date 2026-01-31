#include "Paddle.h"
#include "Core/Component/PlayerController.h"

void Paddle::Init()
{
	AddComponent(new PlayerController(*this, playerNo));
	sprite = {{1, 1}, {1, 1}};
	newSprite = new int[2 * 2]{1, 1, 1, 1};
}
