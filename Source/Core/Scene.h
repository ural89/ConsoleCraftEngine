#pragma once
#include "../Core.h"
#include <vector>
#include <map>
#include "GameObject.h"
#include "Collision.h"
#include "Camera.h"
#include <queue>
#include <algorithm>
class GE_API Scene
{
protected:
	std::vector<GameObject *> GameObjects;
	std::queue<GameObject *> gameObjectsToSpawn;
	std::map<std::string, GameObject *> NameToGameObjectMap;

public:
	Scene();
	virtual ~Scene();
	virtual void Init(){};

	Camera *camera;
	class UIHandler *uiHandler;
	void AddGameObject(GameObject *gameObject)
	{
		gameObjectsToSpawn.push(gameObject);
	}
	void AddGameObject(GameObject *gameObject, Vector2 position)
	{
		gameObjectsToSpawn.push(gameObject);
		gameObject->transform.Position = position;
	}
	void RemoveGameObject(GameObject *gameObject)
	{
		auto it = std::find(GameObjects.begin(), GameObjects.end(), gameObject);
		if (it != GameObjects.end())
		{
			delete *it;
			GameObjects.erase(it);
		}
		collision.RemoveGameObject(gameObject);
	}
	void UpdateCamera(float deltaTime)
	{
		camera->UpdateCamera(deltaTime);
		if (camera->isMoving)
		{
			for (auto &go : GetGameObjects())
			{
				go->transform.MovePosition(camera->offsetX * deltaTime, camera->offsetY * deltaTime, true);
			}
			camera->offsetX = 0;
			camera->offsetY = 0;
		}
	}
	virtual void Update(float deltaTime)
	{
		if (isPaused)
			return;
		for (auto &go : GetGameObjects())
		{

			go->Update(deltaTime);
			go->UpdateComponents(deltaTime);
		}
		for (auto &go : GetGameObjects())
		{
			if (go->isDestroyedFlag)// && (go->hasClearedFromScreen || !go->isRenderable))
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

			GameObject *go = gameObjectsToSpawn.front();
			InitializeGameObject(go);
			gameObjectsToSpawn.pop();
		}
	}
	GameObject *FindNearestGameObject(Transform transform, std::string gameObjectName)
	{
		GameObject *nearestGameObject = nullptr;
		float nearestDistance = std::numeric_limits<float>::max();

		for (auto &go : GameObjects)
		{
			if (go->name == gameObjectName && go->canFindable)
			{
				float distanceToGameObject = Vector2::Distance(transform.Position, go->transform.Position);

				if (distanceToGameObject < nearestDistance)
				{
					nearestGameObject = go;
					nearestDistance = distanceToGameObject;
				}
			}
		}

		return nearestGameObject;
	}
	GameObject *FindSecondNearestGameObject(Transform transform, std::string gameObjectName)
	{
		GameObject *nearestGameObject = nullptr;
		float nearestDistance = std::numeric_limits<float>::max();
		GameObject *secondNearestGameObject = nullptr;
		float secondNearestDistance = std::numeric_limits<float>::max();

		for (auto &go : GameObjects)
		{
			if (go->name == gameObjectName)
			{
				float distanceToGameObject = Vector2::Distance(transform.Position, go->transform.Position);

				if (distanceToGameObject < nearestDistance)
				{
					secondNearestGameObject = nearestGameObject;
					secondNearestDistance = nearestDistance;

					nearestGameObject = go;
					nearestDistance = distanceToGameObject;
				}
				else if (distanceToGameObject < secondNearestDistance)
				{
					secondNearestGameObject = go;
					secondNearestDistance = distanceToGameObject;
				}
			}
		}

		return secondNearestGameObject;
	}
	GameObject *FindGameObject(std::string gameObjectName)
	{
		GameObject *gameObject = nullptr;

		for (auto &go : GameObjects)
		{
			if (go->name == gameObjectName)
			{

				gameObject = go;
			}
		}

		return gameObject;
	}
	const std::vector<GameObject *> &GetGameObjects() const
	{
		return GameObjects;
	}

	GameObject *GetGameObject(std::string name)
	{
		return NameToGameObjectMap[name];
	}

	bool hasGameOver = false;
	bool isPaused = false;

private:
	Collision collision;
	void InitializeGameObject(GameObject *go);
};