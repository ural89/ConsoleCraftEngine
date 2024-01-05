#pragma once
#include "Core/Component/Component.h"
#include "Core/UIHandler.h"
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

	void DrawUpgradeSquare();
};

