#pragma once
#include "Core/GameObject.h"
class BuildingTrigger : public GameObject
{
public:
	BuildingTrigger(class Scene& scene, Vector2 size, GameObject& owner) : GameObject("Trigger", scene), size(size), owner(owner) {
		Sprite sprite = { {0} };
        SetSprite(sprite);
	}
	void OnCollided(GameObject& other) override;
	void OnCollisionExit(GameObject& other) override;

	class Road* mainConnectionRoad;
	bool HasRoad = false;
	bool HasElectricity = false;
	bool HasWater = false;

	int GetWidth() const override
	{
		return size.X;
	}
	int GetHeight() const override
	{
		return size.Y;
	}


private:
	Vector2 size;
	GameObject& owner;
};

