#include "RTSScene.h"
#include "GameObjects/Unit.h"
#include "GameObjects/SelectCursor.h"
#include "Component/AI/AIMovement.h"
#include "Input.h"

void RTSScene::Init()
{
    auto unit = new Unit(*this);
    AddGameObject(unit, Vector2(5,5));

    auto unitTarget = new Unit(*this);
    AddGameObject(unitTarget, Vector2(35,4));
    unitTarget->isNavIgnore = true;

    m_SelectCursor = new SelectCursor(*this);
    AddGameObject(m_SelectCursor, Vector2(35, 10));


    auto inputEvent = BIND_EVENT_FN(RTSScene::OnInput);
    Input::AddListener(inputEvent);
    auto aiMovementComponent = new AIMovement(*unit);
    aiMovementComponent->SetTargetTransform(&unitTarget->transform);
    unit->AddComponent(aiMovementComponent);
}

void RTSScene::OnInput(int input)
{
	float cameraMoveSpeed = 1;
	if (std::tolower(input) == 'd')
	{
		m_SelectCursor->transform.MovePosition(cameraMoveSpeed, 0);
		camera->MoveCameraLeft();
	}
	if (std::tolower(input) == 'a')
	{
		m_SelectCursor->transform.MovePosition(-cameraMoveSpeed, 0);
		camera->MoveCameraRight();
	}
	if (std::tolower(input) == 'w')
	{
		m_SelectCursor->transform.MovePosition(0, cameraMoveSpeed);
		camera->MoveCameraUp();
	}
	if (std::tolower(input) == 's')
	{
		m_SelectCursor->transform.MovePosition(0, -cameraMoveSpeed);
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

