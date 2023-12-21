#pragma once
#include "../Core.h"
#include "../CoreStructs/Transform.h"
#include <vector>
class GE_API GameObject
{
public:
	GameObject(std::string name) : name(name) {};
	std::string name;
	std::vector<std::vector<int>> sprite;
	Transform transform = Transform();
	
	int GetWidth() { return sprite[0].size(); }
	int GetHeight() { return sprite[1].size(); }

	virtual void OnCollided(const GameObject& other)
	{ 
		//std::cout << "collided with " + other.name << '\n'; 
	};
	virtual void Init() {};
	virtual void Update(float deltaTime) {};
	
	std::string symbol = " ";

};