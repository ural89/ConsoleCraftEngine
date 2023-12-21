#pragma once
#include "Core/Scene.h"


class PongScene : public Scene
{

public:
	PongScene();

	~PongScene() override
	{
		std::cout << "Destructed main scene" << '\n';
	}

};
