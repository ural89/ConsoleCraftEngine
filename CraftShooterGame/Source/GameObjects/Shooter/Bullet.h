#pragma once
#include "Core\GameObject.h"
class Bullet : public GameObject
{
public:
	Bullet(class Scene& scene) : GameObject("Bullet", scene) 
	{
		symbol = '#';
	}
	void Init() override;
	void Update(float deltaTime) override;
	void OnCollidedBorder() override;
	virtual void OnCollided(const GameObject& other) override;
};

