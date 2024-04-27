#pragma once

#include "Core/GameObject.h"
#include "Event/EventDispatcher.h"
#include "Event/Event.h"

class Enemy : public GameObject
{
public:
	Enemy(class Scene& scene) : GameObject("Enemy", scene)
	{
		symbol = '\xDB';
		
	}
	void Init() override;
	void Update(float deltaTime) override;

	virtual void OnCollided(GameObject& other) override;
	virtual void OnCollidedBorder() override;
private:
	class ParticleSource* particleSource;
};

