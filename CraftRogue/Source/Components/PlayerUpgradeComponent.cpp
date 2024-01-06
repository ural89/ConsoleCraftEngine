#include "PlayerUpgradeComponent.h"
#include "Core/GameObject.h"
#include "Core/Scene.h"
#include "Core/UIHandler.h"

PlayerUpgradeComponent::PlayerUpgradeComponent(GameObject &gameObject) : Component(gameObject)
{
}

void PlayerUpgradeComponent::Init()
{
    UpgradeUiData.position = Vector2(2, 6);

    UpgradeUiDataPtr = std::make_shared<UIData>(UpgradeUiData);

    owner->GetCurrentScene().uiHandler->AddString(UpgradeUiDataPtr);

}

void PlayerUpgradeComponent::DrawUpgradeSquare()
{
   

    const int size = 11;

    UpgradeUiDataPtr->text += "Level Up! \r \n";

    UpgradeUiDataPtr->text += " 1. Plasma gun \r \n";

    UpgradeUiDataPtr->text += " 2. Blast gun \r \n";

    UpgradeUiDataPtr->text += " 3. Thunder gun \r";

    UpgradeUiDataPtr->text += '\n';
}

void PlayerUpgradeComponent::AddExperience(int experienceToAdd)
{
    experience += experienceToAdd;
    if (experience >= 1)
    {
        DrawUpgradeSquare();
        owner->GetCurrentScene().isPaused = true;
    }
}
