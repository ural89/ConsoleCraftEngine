#include "Scenes/MatchScene.h"
#include "Core/EntryPoint.h"
#include <vector>
class CraftMatchGame
{
public:
    ~CraftMatchGame()
    {
    }
    Engine engine;
    void StartGame()
    {
        engine.scenes.push_back(new MatchScene());
        engine.StartGame();
    }
    void Clean()
    {
        engine.Clean();
    }
};

int main()
{
    CraftMatchGame *game = new CraftMatchGame();
    game->StartGame();
    game->Clean();
    delete game;
    system("pause");
    return 0;
}
