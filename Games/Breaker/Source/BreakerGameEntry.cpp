#include "Scenes/BreakerScene.h"
#include "Core/EntryPoint.h"
#include <vector>
class BreakerGame
{
public:
    ~BreakerGame()
    {
    }
    Engine engine;
    void StartGame()
    {
        engine.scenes.push_back(new BreakerScene());
        engine.StartGame();
    }
    void Clean()
    {
        engine.Clean();
    }
};

int main()
{
    BreakerGame *game = new BreakerGame();
    game->StartGame();
    game->Clean();
    delete game;
    system("pause");
    return 0;
}
