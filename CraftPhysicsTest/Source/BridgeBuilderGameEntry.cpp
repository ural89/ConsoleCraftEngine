#include "Scenes/PhysicsTestScene.h"
#include "Core/EntryPoint.h"
#include <vector>
class BridgeBuilder
{
public:
    ~BridgeBuilder()
    {
    }
    Engine engine;
    void StartGame()
    {
        engine.scenes.push_back(new PhysicsTestScene());
        engine.StartGame();
    }
    void Clean()
    {
        engine.Clean();
    }
};

int main()
{
    BridgeBuilder *game = new BridgeBuilder();
    game->StartGame();
    game->Clean();
    delete game;
    system("pause");
    return 0;
}
