#pragma once
#include "Core\Scene.h"
class MatchScene : public Scene
{
public:
	void Init() override;
private:
	void CreateGrid(int width, int height);
};

