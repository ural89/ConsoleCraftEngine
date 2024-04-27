#pragma once

#include "Input/Input.h"
#include "Graphics/Renderer.h"
#include "Graphics/Scene.h"

class Engine
{
public:
    std::vector<Scene*> scenes;
    
    void StartGame()
    {
        SetCurrentScene(scenes[0]);

        auto startTime = std::chrono::high_resolution_clock::now();
        auto prevTime = startTime;

        while (Input::GetKeyDown() != 27)
        {
            auto endTime = std::chrono::high_resolution_clock::now();
            auto deltaTimeInSeconds = std::chrono::duration_cast<std::chrono::duration<double>>(endTime - prevTime).count();
            double deltaTimeMilliseconds = deltaTimeInSeconds * 1000.0;

            if (currentScene->hasGameOver)
                return;
            UpdateInput();
            Update(static_cast<float>(deltaTimeInSeconds));
            Render();
            UpdateCamera(static_cast<float>(deltaTimeInSeconds));
            if (currentScene->camera->isMoving)
                Render();
            prevTime = endTime;
        }
    }
    void Clean()
    {
        delete currentScene;
        Input::Cleanup();
    }
    void InitScene(Scene *scene)
    {
        scene->Init();
    }

private:
    Scene *currentScene;
    Renderer renderer;
    void UpdateInput()
    {
        Input::Update();
    }
    void Update(float deltaTime)
    {
        currentScene->Update(deltaTime);
        currentScene->SpawnQueuedGameObjects();
    }
    void UpdateCamera(float deltaTime)
    {
        currentScene->UpdateCamera(deltaTime);
    }
    void Render()
    {
        renderer.Render(*currentScene);
    }
    void SetCurrentScene(Scene *scene)
    {
        currentScene = scene;
        InitScene(currentScene);
    }
};