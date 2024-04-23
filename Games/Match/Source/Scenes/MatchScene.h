#pragma once
#include "Core/Scene.h"
class MatchScene : public Scene
{
public:
	~MatchScene() override;
	void Init() override;
	void Update(float deltaTime) override;
	class Grid* grid;
	
private:
	void CreateGrid(int width, int height);
	class UnitSelector* unitSelector = nullptr;

};

