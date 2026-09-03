#include "Scenes/BridgeScene.h"
#include "Core/EntryPoint.h"
#include <vector>

class CraftBridge
{
public:
    ~CraftBridge()
    {
    };

    Engine engine;

    void StartGame()
    {
        engine.scenes.push_back(new BridgeScene());
        engine.StartGame();
    }

    void Clean()
    {
        engine.Clean();
    }
};

int main()
{
    CraftBridge *game = new CraftBridge();
    game->StartGame();
    game->Clean();
    delete game;
    system("pause");
    return 0;
}
