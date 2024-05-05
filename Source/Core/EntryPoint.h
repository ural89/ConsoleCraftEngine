#include <thread>
#include <Core/Input.h>
#include "Core/Renderer.h"
#include "Core/Scene.h"
#include "Core/SceneManager.h"
#include <vector>
class Engine
{
public:
   // SceneManager sceneManager;
    std::vector<Scene *> scenes;

    void StartGame()
    {
        SceneManager::ChangeScene(scenes[0]);
       // SetCurrentScene(SceneManager::CurrentScene);
        auto startTime = std::chrono::high_resolution_clock::now();
        auto prevTime = startTime;

        while (Input::GetKeyDown() != 27)
        {
            if (SceneManager::CurrentScene != nullptr)
            {
                auto endTime = std::chrono::high_resolution_clock::now();
                auto deltaTimeInSeconds = std::chrono::duration_cast<std::chrono::duration<double>>(endTime - prevTime).count();
                //  double deltaTimeMilliseconds = deltaTimeInSeconds * 1000.0;

                if (SceneManager::CurrentScene->hasGameOver)
                    return;
                UpdateInput();
                Update(deltaTimeInSeconds);
                Render();
                prevTime = endTime;
            }
        }
    }
    void Clean()
    {
        delete SceneManager::CurrentScene;
        Input::Cleanup();
    }
    void InitScene(Scene *scene)
    {
        scene->Init();
        scene->Start();
    }

private:
    Renderer renderer;
    void UpdateInput()
    {
        Input::Update();
    }
    void Update(float deltaTime)
    {
        SceneManager::CurrentScene->Update(deltaTime);
        SceneManager::CurrentScene->SpawnQueuedGameObjects();
    }
    void UpdateCamera(float deltaTime)
    {
        SceneManager::CurrentScene->UpdateCamera(deltaTime);
    }
    void Render()
    {
        renderer.Render(*SceneManager::CurrentScene);
    }
    void SetCurrentScene(Scene *scene)
    {
#ifdef __GNUC__
        system("clear");
#else
        system("cls");
#endif
       // currentScene = scene;
        InitScene(SceneManager::CurrentScene);
    }
};