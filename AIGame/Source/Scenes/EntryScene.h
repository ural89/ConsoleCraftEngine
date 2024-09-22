#pragma once
#include "Core/Scene.h"
// #include "Core/AI/Pathfinder.h"

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
    // std::unique_ptr<Pathfinder> m_Pathfinding = std::make_unique<Pathfinder>(*this);

};

