#include "Scene.h"
Scene::Scene()
{
	camera = new Camera();
}
Scene::~Scene()
{
	for (auto& go : GetGameObjects())
	{
		delete go;
	}
	std::cout << "Destructed  scene" << '\n';
	delete camera;
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
