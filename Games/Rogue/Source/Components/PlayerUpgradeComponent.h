#pragma once

#include "Core/Component.h"
#include "Graphics/UIHandler.h"

// @TODO: Look into this - do we need to forward declare here!!!!


class PlayerUpgradeComponent : public Component
{
public:
	PlayerUpgradeComponent(class GameObject& gameObject);

	void Init() override;
	void AddExperience(int experienceToAdd);
	bool isInUpgrade = false;
private:
	int experience = 0;
	int experienceCap = 4;
	UIData UpgradeUiData;
	std::shared_ptr<UIData> UpgradeUiDataPtr;

	UIData experienceUiData;
	std::shared_ptr<UIData> experienceUiDataPtr;

	std::function<void(int)> inputEvent;
	void CreateUpgradeSquare();
	void OnKeyPress(int input);
};

