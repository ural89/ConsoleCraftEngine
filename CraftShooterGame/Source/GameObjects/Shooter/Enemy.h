#pragma once
#include "Core/GameObject.h"
#include "Core/EventDispatcher.h"
#include "Core/Event.h"
class Enemy : public GameObject
{
public:
	Enemy(class Scene& scene) : GameObject("Enemy", scene)
	{
		symbol = '\xDB';
		
	}
	void Init() override{ 
		color = 4;
		sprite = { {1,1}, {1,1} }; 
	}
	void Update(float deltaTime) override;

	virtual void OnCollided(const GameObject& other) override;
	virtual void OnCollidedBorder() override;
};

