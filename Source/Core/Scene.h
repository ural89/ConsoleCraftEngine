#pragma once
#include "../Core.h" 
#include <vector>
#include <map>
#include "GameObject.h"
#include "Collision.h"
#include "Camera.h"
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
	virtual void Init() {};

	Camera* camera;
	void AddGameObject(GameObject* gameObject)
	{	
		gameObjectsToSpawn.push(gameObject);
	}
	void AddGameObject(GameObject* gameObject, Vector2 position)
	{
		gameObjectsToSpawn.push(gameObject);
		gameObject->transform.Position = position;

	}
	void RemoveGameObject(GameObject* gameObject)
	{
		// auto it = std::find(GameObjects.begin(), GameObjects.end(), gameObject);
		// if (it != GameObjects.end())
		// {
		// 	delete* it; 
		// 	GameObjects.erase(it); 
		// }
		// collision.RemoveGameObject(gameObject);
	}
	void UpdateCamera(float deltaTime)
	{
		camera->UpdateCamera(deltaTime);
		if (camera->isMoving)
			for (auto& go : GetGameObjects())
			{
				go->transform.MovePosition(camera->offsetX, camera->offsetY);
			}

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

	bool hasGameOver = false;
private:
	Collision collision;
	void InitializeGameObject(GameObject* go);
};