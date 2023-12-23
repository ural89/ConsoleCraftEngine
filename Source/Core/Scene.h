#pragma once
#include "../Core.h" 
#include <vector>
#include <map>
#include "GameObject.h"
#include "Collision.h"
#include <queue>
class GE_API Scene
{
protected:
	std::vector<GameObject*> GameObjects;
	std::queue<GameObject*> gameObjectsToSpawn;
	std::map<std::string, GameObject*> NameToGameObjectMap;
public:
	Scene();
	virtual ~Scene();
	virtual void CreateGameObjects() {};


	void AddGameObject(GameObject* gameObject)
	{	
		//TODO: create queue game objects to spawn
		gameObjectsToSpawn.push(gameObject);
		//InitializeGameObject(gameObject);	
	}
	void AddGameObject(GameObject* gameObject, Vector2 position)
	{
		gameObjectsToSpawn.push(gameObject);
		gameObject->transform.Position = position;
		//InitializeGameObject(gameObject);
	}
	void RemoveGameObject(GameObject* gameObject)
	{
		auto it = std::find(GameObjects.begin(), GameObjects.end(), gameObject);
		if (it != GameObjects.end())
		{
			delete* it; 
			GameObjects.erase(it); 
		}
		collision.RemoveGameObject(gameObject);
	}
	virtual void Update(float deltaTime)
	{
		for (auto& go : GetGameObjects())
		{
			go->Update(deltaTime);
			go->UpdateComponents(deltaTime);
			
		}
		for (auto& go : GetGameObjects())
		{
			if (go->isDestroyedFlag && go->hasClearedFromScreen)
			{
				RemoveGameObject(go);

			}
		}
		collision.CheckForCollisions();
		collision.CheckForBorderCollisions();
	}
	void SpawnQueuedGameObjects()
	{
		while (!gameObjectsToSpawn.empty())
		{
			GameObject* go = gameObjectsToSpawn.front();
			InitializeGameObject(go);
			//delete go;
			gameObjectsToSpawn.pop();

		}
	}
	const std::vector<GameObject*>& GetGameObjects() const
	{
		return GameObjects;
	}
	

	GameObject* GetGameObject(std::string name) 
	{
		return NameToGameObjectMap[name];
	}
private:
	Collision collision;
	void InitializeGameObject(GameObject* go);
};