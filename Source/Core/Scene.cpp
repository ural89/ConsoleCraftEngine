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

	b2Body *groundBody = World->CreateBody(&borderDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(SCREENWIDTH, 1.f);
	groundBody->CreateFixture(&groundBox, 0);

	borderDef.position.Set(0, 0);
	b2Body *topBody = World->CreateBody(&borderDef);
	b2PolygonShape topBox;
	topBox.SetAsBox(SCREENWIDTH, 1.f);
	topBody->CreateFixture(&topBox, 0);

	borderDef.position.Set(SCREENWIDTH, 0);
	b2Body *rightBody = World->CreateBody(&borderDef);
	b2PolygonShape rightBox;
	rightBox.SetAsBox(1, SCREENHEIGHT);
	rightBody->CreateFixture(&rightBox, 0);

	borderDef.position.Set(0, 0);
	b2Body *leftBody = World->CreateBody(&borderDef);
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
	for (auto &p : polygons)
	{
		delete p;
	}
	std::cout << "Destructed  scene" << '\n';
	delete camera;
	delete uiHandler;
	delete collisionResolver;
	delete raycaster;
	delete World;
	World = nullptr;
}

void Scene::InitializeGameObject(GameObject *go)
{
	GameObjects.push_back(go);
	NameToGameObjectMap.insert({go->name, go});
	go->Init();

	if (go->hasCollider)
		collision.AddGameObject(go);
}

void Scene::InitializePolygon(Polygon *p)
{
	polygons.push_back(p);
	// p->Init();
	polygonCollision.AddPolygon(p);
}
