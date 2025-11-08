#pragma once
#include "../Core.h"
#include <vector>
#include <map>
#include "GameObject.h"
#include "Physics/Polygon/Polygon.h"
#include "Physics/CollisionResolver.h"
#include "Component/AI/Pathfinder.h"
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
	std::vector<GameObject *> m_GameObjects;
	std::queue<GameObject *> m_GameObjectsToSpawn;
	std::map<std::string, GameObject *> m_NameToGameObjectMap;
	std::vector<Polygon *> m_Polygons;
	std::queue<Polygon *> m_PolygonsToSpawn;

public:
	Scene();

	virtual ~Scene();
	virtual void Init(){};
	virtual void Start(){};
    GameObject* CreateGameObject(std::string &&name, Vector2 position)
    {
        GameObject* newGameObject = new GameObject(std::move(name), *this);
        AddGameObject(newGameObject, position);
        return newGameObject;
    }

	void AddGameObject(GameObject *gameObject);
	void AddGameObject(GameObject *gameObject, Vector2 position);
	void AddPolygon(Polygon *polygon);
	void RemovePolygon(Polygon *polygon);
	void UpdateCamera(float deltaTime);
	virtual void Update(float deltaTime); //!!ALWAYS UPDATE BASE HERE
	void SpawnQueuedGameObjects();
	GameObject *FindNearestGameObject(Transform transform, std::string gameObjectName);
	GameObject *FindSecondNearestGameObject(Transform transform, std::string gameObjectName);
	GameObject *FindGameObject(std::string gameObjectName);
	const std::vector<GameObject *> &GetGameObjects() const
	{
		return m_GameObjects;
	}

	GameObject *GetGameObject(std::string name)
	{
		return m_NameToGameObjectMap[name];
	}

public:
	bool hasGameOver = false;
	bool isPaused = false;

	Camera *camera;
	class UIHandler *uiHandler;
	CollisionResolver *collisionResolver; // Reached from rigidbodies to be added

	Collision collision;
	b2World *world = new b2World(b2Vec2(0, 20));
	Raycaster *raycaster = new Raycaster(*this);
	Pathfinder *pathfinder = new Pathfinder(*this);


private:
	void RemoveGameObject(GameObject *gameObject);
	void CreateBoxBorder();
	void InitializeGameObject(GameObject *go);
	void InitializePolygon(Polygon *p);

private:
	PolygonCollision polygonCollision;
	std::shared_ptr<UIData> debugUIPtr;

	int32 velocityIterations = 6;
	int32 positionIterations = 2;
};
