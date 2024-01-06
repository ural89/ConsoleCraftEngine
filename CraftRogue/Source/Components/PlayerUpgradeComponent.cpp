#include "PlayerUpgradeComponent.h"
#include "Core/GameObject.h"
#include "Core/Scene.h"
#include "Core/UIHandler.h"
PlayerUpgradeComponent::PlayerUpgradeComponent(GameObject& gameObject) : Component(gameObject)
{
}

void PlayerUpgradeComponent::Init()
{
	UpgradeUiData.position = Vector2(0, 5);
    
	UpgradeUiDataPtr = std::make_shared<UIData>(UpgradeUiData);

    owner->GetCurrentScene().uiHandler->AddString(UpgradeUiDataPtr);
	
}

void PlayerUpgradeComponent::DrawUpgradeSquare()
{
    const int size = 11;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (i == 0 || i == size - 1 || j == 0 || j == size - 1) {
                if (i % 2 == 0)
                    UpgradeUiDataPtr->text += "* ";
            }
            else if (j == 3 && i == 1) {
                UpgradeUiDataPtr->text += "Level Up! ";
            }
            else if (j == 2 && i == 3) {
                UpgradeUiDataPtr->text += "1. Plasma gun";
            }
            else if (j == 2 && i == 5) {
                UpgradeUiDataPtr->text += "2. Blast gun";
            }
            else if (j == 2 && i == 7) {
                UpgradeUiDataPtr->text += "3. Thunder gun";
            }
            else {
                UpgradeUiDataPtr->text += "  ";
            }
        }
        UpgradeUiDataPtr->text += '\n';
    }
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
