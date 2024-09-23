#include "Scene.h"
#include "UIHandler.h"
#include "Input.h"
Scene::Scene()
{
	camera = new Camera();
	uiHandler = new UIHandler();
	collisionResolver = new CollisionResolver(*this);

	debugUIPtr = std::make_shared<UIData>();
	debugUIPtr->position = Vector2(5, 29);
	uiHandler->AddString(debugUIPtr);

	CreateBoxBorder();
}
void Scene::CreateBoxBorder()
{
	// Create ground body
	b2BodyDef borderDef;
	borderDef.position.Set(0, SCREENHEIGHT);

	b2Body *groundBody = world->CreateBody(&borderDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(SCREENWIDTH, 1.f);
	groundBody->CreateFixture(&groundBox, 0);

	borderDef.position.Set(0, 0);
	b2Body *topBody = world->CreateBody(&borderDef);
	b2PolygonShape topBox;
	topBox.SetAsBox(SCREENWIDTH, 1.f);
	topBody->CreateFixture(&topBox, 0);

	borderDef.position.Set(SCREENWIDTH, 0);
	b2Body *rightBody = world->CreateBody(&borderDef);
	b2PolygonShape rightBox;
	rightBox.SetAsBox(1, SCREENHEIGHT);
	rightBody->CreateFixture(&rightBox, 0);

	borderDef.position.Set(0, 0);
	b2Body *leftBody = world->CreateBody(&borderDef);
	b2PolygonShape leftBox;
	leftBox.SetAsBox(1, SCREENHEIGHT);
	leftBody->CreateFixture(&leftBox, 0);
}
Scene::~Scene()
{
	Input::Cleanup();
	for (auto &go : GetGameObjects())
	{
		if (go != nullptr)
			delete go;
	}
	for (auto &p : m_Polygons)
	{
		delete p;
	}
	std::cout << "Destructed  scene" << '\n';
	delete camera;
	delete uiHandler;
	delete collisionResolver;
	delete raycaster;
	delete world;
	delete pathfinder;
	pathfinder = nullptr;
	camera = nullptr;
	uiHandler = nullptr;
	world = nullptr;
}

void Scene::AddGameObject(GameObject *gameObject)
{
	m_GameObjectsToSpawn.push(gameObject);
}

void Scene::AddGameObject(GameObject *gameObject, Vector2 position)
{
	m_GameObjectsToSpawn.push(gameObject);
	gameObject->transform.Position = position;
}

void Scene::RemoveGameObject(GameObject *gameObject)
{

	auto it = std::find(m_GameObjects.begin(), m_GameObjects.end(), gameObject);
	if (it != m_GameObjects.end())
	{
		delete *it;
		m_GameObjects.erase(it);
	}
	collision.RemoveGameObject(gameObject);
}

void Scene::AddPolygon(Polygon *polygon)
{
	polygon->Init();
	m_PolygonsToSpawn.push(polygon);
}

void Scene::RemovePolygon(Polygon *polygon)
{
	auto it = std::find(m_Polygons.begin(), m_Polygons.end(), polygon);
	if (it != m_Polygons.end())
	{
		delete *it;
		m_Polygons.erase(it);
	}
	polygonCollision.RemovePolygon(polygon);
}

void Scene::UpdateCamera(float deltaTime)
{
	camera->UpdateCamera(deltaTime);
}

void Scene::Update(float deltaTime)
{
	if (isPaused)
		return;
	world->Step(deltaTime, velocityIterations, positionIterations); // TODO: carry this to scene.h
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

	for (auto &p : m_Polygons)
	{
		p->UpdateLines(deltaTime);
	}

	collision.CheckForCollisions();
	collision.CheckForBorderCollisions();
	polygonCollision.UpdateResolve(deltaTime);

	// collisionResolver->UpdateResolve(deltaTime);
	collisionResolver->UpdateBorderResolve(deltaTime);
}

void Scene::SpawnQueuedGameObjects()
{
	while (!m_PolygonsToSpawn.empty())
	{
		Polygon *p = m_PolygonsToSpawn.front();
		InitializePolygon(p);
		m_PolygonsToSpawn.pop();
	}

	while (!m_GameObjectsToSpawn.empty())
	{

		GameObject *go = m_GameObjectsToSpawn.front();
		InitializeGameObject(go);
		m_GameObjectsToSpawn.pop();
	}
}

GameObject *Scene::FindNearestGameObject(Transform transform, std::string gameObjectName)
{
	GameObject *nearestGameObject = nullptr;
	float nearestDistance = std::numeric_limits<float>::max();

	for (auto &go : m_GameObjects)
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

GameObject *Scene::FindSecondNearestGameObject(Transform transform, std::string gameObjectName)
{
	GameObject *nearestGameObject = nullptr;
	float nearestDistance = std::numeric_limits<float>::max();
	GameObject *secondNearestGameObject = nullptr;
	float secondNearestDistance = std::numeric_limits<float>::max();

	for (auto &go : m_GameObjects)
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

GameObject *Scene::FindGameObject(std::string gameObjectName)
{
	GameObject *gameObject = nullptr;

	for (auto &go : m_GameObjects)
	{
		if (go->name == gameObjectName)
		{

			gameObject = go;
		}
	}

	return gameObject;
}

void Scene::InitializeGameObject(GameObject *go)
{
	m_GameObjects.push_back(go);
	m_NameToGameObjectMap.insert({go->name, go});
	go->Init();

	if (go->hasCollider)
		collision.AddGameObject(go);
}

void Scene::InitializePolygon(Polygon *p)
{
	m_Polygons.push_back(p);
	// p->Init();
	polygonCollision.AddPolygon(p);
}
