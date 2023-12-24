#include "Scenes/Pong/PongScene.h"
#include <thread>
#include <Core/Input.h>
#include "Core/Renderer.h"
#include "Scenes/Shooter/ShooterScene.h"
class Game
{
public:
    ~Game()
    {
      
    }
	void StartGame()
	{
        SetCurrentScene(new ShooterScene());

        
        auto startTime = std::chrono::high_resolution_clock::now();
        auto prevTime = startTime;

        while (Input::GetKeyDown() != 27)
        {
            auto endTime = std::chrono::high_resolution_clock::now();
            auto deltaTimeInSeconds = std::chrono::duration_cast<std::chrono::duration<double>>(endTime - prevTime).count();
            double deltaTimeMilliseconds = deltaTimeInSeconds * 1000.0;

            if (currentScene->hasGameOver) return;
            UpdateInput();
            Update(deltaTimeInSeconds);
            Render();
            UpdateCamera(deltaTimeInSeconds);
            Render(); //TODO: fix this workaround for camera shake
            prevTime = endTime;
        }
	}
    void Clean()
    {
        delete currentScene;
        Input::Cleanup();
        
    }
    void InitSceneGameObjects(Scene* scene)
    {
        scene->CreateGameObjects();

    }
private:
 
    Scene* currentScene;
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
    void SetCurrentScene(Scene* scene)
    {
        currentScene = scene;
        InitSceneGameObjects(currentScene);
    }
};

int main()
{
	Game* game =new Game();
	game->StartGame();
    game->Clean();
    delete game;
    system("pause");
	return 0;
}
