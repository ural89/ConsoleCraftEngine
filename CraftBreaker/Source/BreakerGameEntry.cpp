#include "Scenes/BreakerScene.h"
#include <thread>
#include <Core/Input.h>
#include "Core/Renderer.h"

class ShooterGame
{
public:
    ~ShooterGame()
    {
    }
    void StartGame()
    {
        SetCurrentScene(new BreakerScene());

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
            Update(deltaTimeInSeconds);
            Render();
            if (currentScene->camera->isMoving)
            {
                UpdateCamera(deltaTimeInSeconds);
                Render();
            }
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

int main()
{
    ShooterGame *game = new ShooterGame();
    game->StartGame();
    game->Clean();
    delete game;
    system("pause");
    return 0;
}
