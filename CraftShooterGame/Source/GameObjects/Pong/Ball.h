#pragma once
#include "Core/GameObject.h"
#include <Core/Input.h>
class Ball : public GameObject
{
public:
	Ball() : GameObject("Ball", scene) 
	{
		symbol = '#';
	}
	
	
	void Init() override
	{
		newSprite = new int[2 * 2]{1, 1, 1, 1};
		sprite = { {1,1}, {1,1} };
	}
	void Update(float deltaTime) override;
	virtual void OnCollided(GameObject& other) override;
	
	friend std::ostream& operator<<(std::ostream& os, const Ball& ball)
	{
		os << "Ball position: " << ball.transform << "\n";
		return os;
	}
private:

	Vector2 velocity = Vector2(50.f,10.f);
	
};
