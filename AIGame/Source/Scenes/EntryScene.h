#pragma once
#include "Core/Scene.h"

#include <vector>
#include "Core/LineDrawer.h"
#include <memory>
#include "Core/Component/AI/Pathfinder.h"

class EntryScene : public Scene
{
public:
	~EntryScene();
	
	void Init() override;
    void Start() override;
	void Update(float deltaTime) override;


private:
	void OnInput(int input);
	float m_LastTimeSinceCameraMove = 0;
	LineDrawer* m_Linedrawer;
	GameObject* playerShip;
	GameObject* enemy;
};

