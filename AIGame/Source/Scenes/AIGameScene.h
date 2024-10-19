#pragma once
#include "Core/Scene.h"

#include "Core/LineDrawer.h"
#include "Core/AIBehavior/Selector.h"

#include <vector>
#include <memory>
class AIGameScene : public Scene
{
public:
	~AIGameScene();
	
	void Init() override;
    void Start() override;
	void Update(float deltaTime) override;


private:
	void OnInput(int input);
	float m_LastTimeSinceCameraMove = 0;
	LineDrawer* m_Linedrawer;
	GameObject* playerShip;
	GameObject* enemy;
    AIBehavior::Selector selector;
};

