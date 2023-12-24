#pragma once
#include "Core/GameObject.h"
#include "Core/Event.h"
#include <functional>
class PlayerShip : public GameObject
{
public:
	PlayerShip(class Scene& scene) : GameObject("PlayerShip", scene)
	{
		symbol = '\xDB';
		
	}
	void Init() override;
	void Update(float deltaTime) override;
	void OnCollided(const GameObject& other) override;
private:
	void Fire(int keyDown);
	void OnEvent(Event& event);
	std::function<void(Event&)> OnEventFunction;
	class ParticleSource* particleSource;
	int score = 0;
};

