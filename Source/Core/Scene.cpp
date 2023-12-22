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



void Scene::InitializeGameObject(GameObject* go)
{
	go->Init();
	go->InitComponents();
	collision.AddGameObject(go);
}
