#pragma once
#include "Core\Scene.h"
class MatchScene : public Scene
{
public:
	~MatchScene() override;
	void Init() override;
	class Grid* grid;
	
private:
	void CreateGrid(int width, int height);
	void CreateItems();

};

