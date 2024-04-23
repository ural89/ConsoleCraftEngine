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

    experienceUiData.position = Vector2(15, SCREENHEIGHT - 1);
    experienceUiData.text = "exp: #";
    experienceUiDataPtr = std::make_shared<UIData>(experienceUiData);
    owner->GetCurrentScene().uiHandler->AddString(experienceUiDataPtr);

    CreateUpgradeSquare();
    inputEvent = std::bind(&PlayerUpgradeComponent::OnKeyPress, this, std::placeholders::_1);
}

void PlayerUpgradeComponent::CreateUpgradeSquare()
{

    UpgradeUiDataPtr->text += "Level Up! \r \n";

    UpgradeUiDataPtr->text += " 1. Plasma gun \r \n";

    UpgradeUiDataPtr->text += " 2. Wave gun \r \n";

    UpgradeUiDataPtr->text += " 3. Blast gun \r";

    UpgradeUiDataPtr->text += '\n';
}

void PlayerUpgradeComponent::OnKeyPress(int input)
{

    if (input == KEY1 || input == KEY2 || input == KEY3)
    {

        owner->GetCurrentScene().isPaused = false;
        Input::RemoveListener(inputEvent);
        owner->GetCurrentScene().uiHandler->RemoveString(UpgradeUiDataPtr);
        Player *player = dynamic_cast<Player *>(owner);
        if (player != nullptr)
        {
            if (input == KEY1)
                player->UnlockWeapon(0);
            else if(input == KEY2)
                player->UnlockWeapon(1);
            else if(input == KEY3)
                player->UnlockWeapon(2);
        }
        isInUpgrade = false;
    }
}

void PlayerUpgradeComponent::AddExperience(int experienceToAdd)
{
    experience += experienceToAdd;
    experienceUiDataPtr->text += "#";
    if (experience >= experienceCap)
    {

        Input::AddListener(inputEvent);
        isInUpgrade = true;
        experienceUiDataPtr->text = "exp: #";
        owner->GetCurrentScene().uiHandler->AddString(UpgradeUiDataPtr);
        experience = 0;
        experienceCap++;
        owner->GetCurrentScene().isPaused = true;
    }
}
