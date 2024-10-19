#include "Scenes/AIGameScene.h"
#include "Core/EntryPoint.h"
#include <vector>
class AIGame
{
public:
    ~AIGame()
    {
    };
    Engine engine;
    void StartGame()
    {
        engine.scenes.push_back(new AIGameScene());
        engine.StartGame();
    }
    void Clean()
    {
        engine.Clean();
    }
};

int main()
{
    AIGame *game = new AIGame();
    game->StartGame();
    game->Clean();
    delete game;
    system("pause");
    return 0;
}
