#include "SceneManager.h"
Scene *SceneManager::CurrentScene = nullptr;
SceneManager::SceneManager()
{
    CurrentScene = nullptr;
}

void SceneManager::ChangeScene(Scene *scene)
{
    //TODO: scene cleanup
    CurrentScene = scene;
    CurrentScene->Init();
    CurrentScene->Start();
#ifdef __GNUC__
    system("clear");
#else
    system("cls");
#endif
}
