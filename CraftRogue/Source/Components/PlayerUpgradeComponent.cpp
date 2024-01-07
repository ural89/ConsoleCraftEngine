#include "PlayerUpgradeComponent.h"
#include "Core/GameObject.h"
#include "Core/Scene.h"
#include "Core/Input.h"

PlayerUpgradeComponent::PlayerUpgradeComponent(GameObject &gameObject) : Component(gameObject)
{
}

void PlayerUpgradeComponent::Init()
{
    UpgradeUiData.position = Vector2(2, 6);

    UpgradeUiDataPtr = std::make_shared<UIData>(UpgradeUiData);

    

    inputEvent = std::bind(&PlayerUpgradeComponent::OnKeyPress, this, std::placeholders::_1);
    Input::AddListener(inputEvent);
}

void PlayerUpgradeComponent::DrawUpgradeSquare()
{

    UpgradeUiDataPtr->text += "Level Up! \r \n";

    UpgradeUiDataPtr->text += " 1. Plasma gun \r \n";

    UpgradeUiDataPtr->text += " 2. Blast gun \r \n";

    UpgradeUiDataPtr->text += " 3. Thunder gun \r";

    UpgradeUiDataPtr->text += '\n';
}

void PlayerUpgradeComponent::OnKeyPress(int input)
{
    if (input == 49)
    {
        owner->GetCurrentScene().isPaused = false;
        Input::RemoveListener(inputEvent);
        UpgradeUiDataPtr->text = "";
        owner->GetCurrentScene().uiHandler->RemoveString(UpgradeUiDataPtr);
    }
}

void PlayerUpgradeComponent::AddExperience(int experienceToAdd)
{
    experience += experienceToAdd;
    if (experience >= 1)
    {
        owner->GetCurrentScene().uiHandler->AddString(UpgradeUiDataPtr);
        experience = 0;
        DrawUpgradeSquare();
        owner->GetCurrentScene().isPaused = true;
    }
}
