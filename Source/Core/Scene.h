#pragma once
#include "../Core.h"
#include <vector>
#include <map>
#include "GameObject.h"
#include "Physics/Polygon/Polygon.h"
#include "Physics/CollisionResolver.h"
#include "Physics/Polygon/PolygonCollision.h"
#include "../box2d/include/box2d/box2d.h"
#include "Physics/Raycaster.h"
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
	std::vector<Polygon *> polygons;
	std::queue<Polygon *> polygonsToSpawn;

public:
	Scene();

	virtual ~Scene();
	virtual void Init(){};
	virtual void Start(){};

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
	void AddPolygon(Polygon *polygon)
	{
		polygon->Init();
		polygonsToSpawn.push(polygon);
	}
	void RemovePolygon(Polygon *polygon)
	{
		auto it = std::find(polygons.begin(), polygons.end(), polygon);
		if (it != polygons.end())
		{
			delete *it;
			polygons.erase(it);
		}
		polygonCollision.RemovePolygon(polygon);
	}
	void UpdateCamera(float deltaTime)
	{
		camera->UpdateCamera(deltaTime);
	}
	virtual void Update(float deltaTime) //!!ALWAYS UPDATE BASE HERE
	{
		if (isPaused)
			return;
		World->Step(deltaTime, velocityIterations, positionIterations); // TODO: carry this to scene.h
		for (auto &go : GetGameObjects())
		{
			float substep = 1;
			for (int i = 0; i < substep; i++) // substep
			{
				go->Update(deltaTime / substep);
				go->UpdateComponents(deltaTime / substep);
			}
		}

		for (auto &go : GetGameObjects()) // destroy flagged gameobjects
		{
			if (go->isDestroyedFlag && (go->hasClearedFromScreen || !go->isRenderable))
			{
				RemoveGameObject(go);
			}
		}

		for (auto &p : polygons)
		{
			p->UpdateLines(deltaTime);
		}

		collision.CheckForCollisions();
		collision.CheckForBorderCollisions();
		polygonCollision.UpdateResolve(deltaTime);

		// collisionResolver->UpdateResolve(deltaTime);
		collisionResolver->UpdateBorderResolve(deltaTime);
	}
	void SpawnQueuedGameObjects()
	{
		while (!polygonsToSpawn.empty())
		{
			Polygon *p = polygonsToSpawn.front();
			InitializePolygon(p);
			polygonsToSpawn.pop();
		}

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

	CollisionResolver *collisionResolver; // Reached from rigidbodies to be added

	Collision collision;
	b2World *World = new b2World(b2Vec2(0, 20));
	Raycaster *raycaster = new Raycaster(*this);

private:
	void CreateBoxBorder();
	PolygonCollision polygonCollision;
	std::shared_ptr<UIData> debugUIPtr;
	void InitializeGameObject(GameObject *go);
	void InitializePolygon(Polygon *p);

	int32 velocityIterations = 6;
	int32 positionIterations = 2;
};