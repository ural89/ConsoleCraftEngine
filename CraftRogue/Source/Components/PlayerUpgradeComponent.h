#pragma once
#include "Core/Component/Component.h"
#include "Core/UIHandler.h"
#include <functional>
class PlayerUpgradeComponent : public Component
{
public:
	PlayerUpgradeComponent(class GameObject& gameObject);

	void Init() override;
	void AddExperience(int experienceToAdd);
	bool isInUpgrade = false;
private:
	int experience = 0;

	class UIData UpgradeUiData;
	std::shared_ptr<UIData> UpgradeUiDataPtr;

	class UIData experienceUiData;
	std::shared_ptr<UIData> experienceUiDataPtr;

	std::function<void(int)> inputEvent;
	void DrawUpgradeSquare();
	void OnKeyPress(int input);
};

