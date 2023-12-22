#include "Scene.h"
Scene::Scene()
{

}
Scene::~Scene()
{
	for (auto& go : GetGameObjects())
	{
		delete go;
	}
	std::cout << "Destructed  scene" << '\n';
}

void Scene::InitializeGameObjects()
{
	for (auto& go : GetGameObjects())
	{
		go->Init();
		go->InitComponents();
		collision.AddGameObject(go);
	}
	
}
