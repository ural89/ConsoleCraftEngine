#include "RTSScene.h"
#include "GameObjects/Unit.h"
#include "Input.h"

void RTSScene::Init()
{
    auto unit = new Unit(*this);
    AddGameObject(unit, Vector2(5,5));

    auto unitTarget = new Unit(*this);
    AddGameObject(unitTarget, Vector2(15,5));

    auto inputEvent = BIND_EVENT_FN(RTSScene::OnInput);
    Input::AddListener(inputEvent);
    // aiMovementComponent->SetTargetTransform(&unitTarget->transform);
}

void RTSScene::OnInput(int input)
{
	float cameraMoveSpeed = 1;

	if (std::tolower(input) == 'd')
	{
		// selectCursor->transform.MovePosition(cameraMoveSpeed, 0);
		camera->MoveCameraLeft();
	}
	if (std::tolower(input) == 'a')
	{
		// selectCursor->transform.MovePosition(-cameraMoveSpeed, 0);
		camera->MoveCameraRight();
	}
	if (std::tolower(input) == 'w')
	{
		// selectCursor->transform.MovePosition(0, -cameraMoveSpeed);
		camera->MoveCameraUp();
	}
	if (std::tolower(input) == 's')
	{
		// selectCursor->transform.MovePosition(0, cameraMoveSpeed);
		camera->MoveCameraDown();
	}
	if (std::tolower(input) == 'f')
	{
		// if (auto collidedObject = selectCursor->GetCollidedObject())
		// {
		// 	demolishHandler->Demolish(*collidedObject);
		// 	selectCursor->ResetCollidedObject();
		// }
	}
}
void RTSScene::Update(float deltaTime)
{
    Scene::Update(deltaTime);
}

