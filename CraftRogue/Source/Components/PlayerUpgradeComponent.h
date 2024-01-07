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
	
private:
	int experience = 0;

	class UIData UpgradeUiData;
	std::shared_ptr<UIData> UpgradeUiDataPtr;
	std::function<void(int)> inputEvent;
	void DrawUpgradeSquare();
	void OnKeyPress(int input);
};

