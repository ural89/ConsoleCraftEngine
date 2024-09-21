#pragma once
#include "Core/Scene.h"
#include "Core/AI/Pathfinding.h"
class EntryScene : public Scene
{
public:
	~EntryScene();
	
	void Init() override;
    void Start() override;
	void Update(float deltaTime) override;


private:
    std::unique_ptr<Pathfinding> m_Pathfinding = std::make_unique<Pathfinding>(*this);

};

