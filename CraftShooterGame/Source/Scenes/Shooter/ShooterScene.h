#pragma once
#include "Core/Scene.h"
class ShooterScene : public Scene
{
public:
	

	~ShooterScene() override
	{
		std::cout << "Destructed main scene" << '\n';
	}
	void CreateGameObjects() override;


};

