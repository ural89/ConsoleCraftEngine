#include "PlayerUpgradeComponent.h"
#include "Core/GameObject.h"
#include "Core/Scene.h"
#include "Core/Input.h"
#include "../GameObjects/Player.h"
PlayerUpgradeComponent::PlayerUpgradeComponent(GameObject &gameObject) : Component(gameObject)
{
}

void PlayerUpgradeComponent::Init()
{
    UpgradeUiData.position = Vector2(2, 6);
    UpgradeUiDataPtr = std::make_shared<UIData>(UpgradeUiData);

    experienceUiData.position = Vector2(10, SCREENHEIGHT - 1);
    experienceUiData.text = "exp: #";
    experienceUiDataPtr = std::make_shared<UIData>(experienceUiData);
    owner->GetCurrentScene().uiHandler->AddString(experienceUiDataPtr);
    DrawUpgradeSquare();
    inputEvent = std::bind(&PlayerUpgradeComponent::OnKeyPress, this, std::placeholders::_1);
   
}

void PlayerUpgradeComponent::DrawUpgradeSquare()
{

    UpgradeUiDataPtr->text += "Level Up! \r \n";

    UpgradeUiDataPtr->text += " 1. Plasma gun \r \n";

    UpgradeUiDataPtr->text += " 2. Wave gun \r \n";

    UpgradeUiDataPtr->text += " 3. Blast gun \r";

    UpgradeUiDataPtr->text += '\n';
}

void PlayerUpgradeComponent::OnKeyPress(int input)
{
	if (input == 49 || input == 50 || input == 51)
    {
        
        owner->GetCurrentScene().isPaused = false;
        Input::RemoveListener(inputEvent);
        owner->GetCurrentScene().uiHandler->RemoveString(UpgradeUiDataPtr);
        isInUpgrade = false;
    }
}

void PlayerUpgradeComponent::AddExperience(int experienceToAdd)
{
    //experience += experienceToAdd;
   // experienceUiDataPtr->text += "#";
    if (experience >= 3)
    {
        Input::AddListener(inputEvent);
        isInUpgrade = true;
        experienceUiDataPtr->text = "exp: #";
        owner->GetCurrentScene().uiHandler->AddString(UpgradeUiDataPtr);
        experience = 0;
        //DrawUpgradeSquare();
        owner->GetCurrentScene().isPaused = true;
    }
}
