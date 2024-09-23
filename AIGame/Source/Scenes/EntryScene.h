#pragma once
#include "Core/Scene.h"

#include <vector>
#include "Core/LineDrawer.h"
#include <memory>
#include "Core/AI/Pathfinder.h"

class EntryScene : public Scene
{
public:
	~EntryScene();
	
	void Init() override;
    void Start() override;
	void Update(float deltaTime) override;


private:
	LineDrawer* m_Linedrawer;
	GameObject* playerShip;
	GameObject* enemy;
};

