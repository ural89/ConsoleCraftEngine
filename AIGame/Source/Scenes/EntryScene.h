#pragma once
#include "Core/Scene.h"

#include <vector>
#include "Core/LineDrawer.h"

class EntryScene : public Scene
{
public:
	~EntryScene();
	
	void Init() override;
    void Start() override;
	void Update(float deltaTime) override;


private:
	class Pathfinder* m_Pathfinder;
	LineDrawer* m_Linedrawer;
	GameObject* playerShip;

};

