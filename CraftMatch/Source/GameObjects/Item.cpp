#include "Item.h"

void Item::SetTargetPosition(Vector2 targetPosition)
{
	this->targetPosition = targetPosition;
}

void Item::Init()
{
    targetPosition = transform.Position;
}

void Item::Update(float deltaTime)
{
	if (targetPosition.ToInt() != transform.Position.ToInt())
	{
		//transform.Position = targetPosition;
		//transform.MovePosition(0, 15 * deltaTime);
	}
}
