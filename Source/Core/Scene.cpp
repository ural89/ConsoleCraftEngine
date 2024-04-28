#include "Scene.h"
#include "UIHandler.h"
Scene::Scene()
{
	camera = new Camera();
	uiHandler = new UIHandler();
	collisionResolver = new CollisionResolver(*this);
	
	debugUIPtr = std::make_shared<UIData>();
	debugUIPtr->position = Vector2(5, 29);
	uiHandler->AddString(debugUIPtr);

 
}

Scene::~Scene()
{
	for (auto &go : GetGameObjects())
	{
		delete go;
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

