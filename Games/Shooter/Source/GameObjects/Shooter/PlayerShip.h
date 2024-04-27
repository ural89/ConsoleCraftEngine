#pragma once

#include "Core/GameObject.h"
#include "Event/Event.h"
#include "Graphics/UIHandler.h"

class PlayerShip : public GameObject
{
public:
	PlayerShip(class Scene &scene) : GameObject("PlayerShip", scene)
	{
		symbol = '\xDB';
	}
	void Init() override;
	void Update(float deltaTime) override;
	void OnCollided(GameObject &other) override;

private:
	UIData scoreUIData;
	std::shared_ptr<UIData> scoreUIDataPtr;
	void Fire(int keyDown);
	void OnEvent(Event &event);
	std::function<void(Event &)> OnEventFunction;
	class ParticleSource *particleSource;
	int score = 0;
};
