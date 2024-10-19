#pragma once
#include "Core/Scene.h"
#include "Core/LineDrawer.h"

#include <vector>
#include <memory>

#include "Core/AIBehavior/BehaviorTree.h"

class AIGameScene : public Scene
{
public:
	~AIGameScene();
	
	void Init() override;
    void Start() override;
	void Update(float deltaTime) override;


private:
	AIBehavior::BehaviorTree m_BehaviorTree;
	void OnInput(int input);
	float m_LastTimeSinceCameraMove = 0;
	LineDrawer* m_Linedrawer;
	GameObject* playerShip;
	GameObject* enemy;
};

