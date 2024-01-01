#pragma once
#include "Core/GameObject.h"

class Ball : public GameObject
{
public:
	Ball(class Scene& scene) : GameObject("Ball", scene) 
	{
	
	}
	
	
	void Init() override
	{
        symbol = '0';
		sprite = { {5}};
	}
	void Update(float deltaTime) override;
	virtual void OnCollided(const GameObject& other) override;
	
	friend std::ostream& operator<<(std::ostream& os, const Ball& ball)
	{
		os << "Ball position: " << ball.transform << "\n";
		return os;
	}
private:
    float collideTimer = 0;
	Vector2 velocity = Vector2(8.f, 20.f);
	
};