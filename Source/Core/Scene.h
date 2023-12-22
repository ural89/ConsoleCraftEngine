#pragma once
#include "../Core.h" 
#include <vector>
#include <map>
#include "GameObject.h"
#include "Collision.h"
class GE_API Scene
{
protected:
	std::vector<GameObject*> GameObjects;
	std::map<std::string, GameObject*> NameToGameObjectMap;
public:
	Scene();
	virtual ~Scene();

	void InitializeGameObjects();
	void AddGameObject(GameObject* gameObject)
	{
		GameObjects.push_back(gameObject);
		NameToGameObjectMap.insert({ gameObject->name, gameObject });
		
	}
	void AddGameObject(GameObject* gameObject, Vector2 position)
	{
		GameObjects.push_back(gameObject);
		NameToGameObjectMap.insert({ gameObject->name, gameObject });
		gameObject->transform.Position = position;
	}
	void RemoveGameObject(GameObject* gameObject)
	{
		auto it = std::find(GameObjects.begin(), GameObjects.end(), gameObject);
		if (it != GameObjects.end())
		{
			delete* it; // Delete the object
			//*it = nullptr; // Set the pointer to null in the vector
			GameObjects.erase(it); // Remove the null pointer from the vector
		}
	}
	void Update(float deltaTime)
	{
		for (auto& go : GetGameObjects())
		{
			go->Update(deltaTime);
			go->UpdateComponents(deltaTime);
		}
		collision.CheckForCollisions();
	}
	std::vector<GameObject*> GetGameObjects() const
	{
		return GameObjects;

	}

	GameObject* GetGameObject(std::string name) 
	{
		return NameToGameObjectMap[name];
	}
private:
	Collision collision;
};