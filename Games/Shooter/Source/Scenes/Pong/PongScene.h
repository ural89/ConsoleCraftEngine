#pragma once

#include "Graphics/Scene.h"

class PongScene : public Scene
{

public:
	PongScene();

	~PongScene() override
	{
		std::cout << "Destructed main scene" << '\n';
	}

	void Init() override;
};
