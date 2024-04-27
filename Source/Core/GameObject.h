#pragma once

#include "Core/Component.h"
#include "Math/Transform.h"

class GE_API GameObject
{
public:
	GameObject(std::string name, class Scene& scene) : name(name), scene(scene){};
	virtual ~GameObject() 
	{
		for (auto& component : components)
		{
			delete component;
		}
		components.clear();
		sprite.clear();
	}

	int GetWidth() const 
	{ 
		return static_cast<int>(sprite[0].size()); 
	}
	int GetHeight() const 
	{ 
		return static_cast<int>(sprite.size());
	}

	void Destroy()
	{
		isDestroyedFlag = true;
		transform.HasOwnerDestroyed = true;
	}
	void AddComponent(Component* component)
	{
		components.push_back(component);
	}

	template <typename T>
	T* GetComponent()
	{
		for (auto& component : components)
		{
			
			if (typeid(*component) == typeid(T))
			{
				return dynamic_cast<T*>(component);
			}
		}
		return nullptr; 
	}

	virtual void Init() {};
	virtual void Update(float deltaTime) {};
	virtual void OnCollided(GameObject& other) {};
	virtual void OnCollidedBorder() {};
	
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
	Scene& GetCurrentScene()
	{
		return scene;
	}

public:
	Transform transform = Transform();

	std::string name = "Gameobject";
	std::vector<std::vector<int>> sprite = { {1,1}, {1,1} };

	std::string symbol = "*";
	int overrideColor = -1;

	bool isDestroyedFlag = false;
	bool hasClearedFromScreen = false;
	bool isRenderable = true;
	bool hasCollider = true;
	bool canFindable = true;

protected:
	std::vector<Component*> components;
	Scene& scene;
};