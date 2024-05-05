#pragma once
#include "../Core.h"
#include "Scene.h"
class GE_API SceneManager
{
public:
    static Scene* CurrentScene;
    static void ChangeScene(Scene* scene);
    SceneManager();
private:

    
};