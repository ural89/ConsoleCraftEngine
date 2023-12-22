#pragma once
#include "../Core.h"
#include "../CoreStructs/Transform.h"
#include <vector>
#include "Component/Component.h"
class GE_API GameObject
{
public:
	GameObject(std::string name) : name(name) {};
	virtual ~GameObject() 
	{
		for (auto& component : components)
		{
			delete component;
		}
		components.clear();
	}
	std::string name;
	std::vector<std::vector<int>> sprite;

	Transform transform = Transform();
	
	int GetWidth() const 
	{ 
		return sprite[0].size(); 
	}
	int GetHeight() const 
	{ 
		return sprite[1].size(); 
	}
	void AddComponent(Component* component)
	{
		components.push_back(component);
	}
	virtual void Init() {};
	virtual void Update(float deltaTime) {};
	virtual void OnCollided(const GameObject& other) {};
	
	void InitComponents()
	{
		for (auto& component : components)
		{
			component->Init();
		}
	}
	void UpdateComponents(float deltaTime)
	{
		for (auto& component:components)
		{
			component->Update(deltaTime);
		}
	}
	std::string symbol = " ";
private:
	std::vector<Component*> components;
};