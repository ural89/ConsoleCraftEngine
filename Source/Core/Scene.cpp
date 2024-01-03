#include "Scene.h"
#include "UIHandler.h"
Scene::Scene()
{
	camera = new Camera();
	uiHandler = new UIHandler();
}
Scene::~Scene()
{
	for (auto& go : GetGameObjects())
	{
		delete go;
	}
	std::cout << "Destructed  scene" << '\n';
	delete camera;
	delete uiHandler;
}



void Scene::InitializeGameObject(GameObject* go)
{
	GameObjects.push_back(go);	
	NameToGameObjectMap.insert({ go->name, go });
	go->Init();
	go->InitComponents();
	if (go->hasCollider)
		collision.AddGameObject(go);
}
