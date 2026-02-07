#include "Scenes/Shooter/ShooterScene.h"
#include "Core/EntryPoint.h"
#include <vector>
class ShooterGame
{
public:
    ~ShooterGame()
    {
    }
    Engine engine;
    void StartGame()
    {
        engine.scenes.push_back(new ShooterScene());
        engine.StartGame();
    }
    void Clean()
    {
        engine.Clean();
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
