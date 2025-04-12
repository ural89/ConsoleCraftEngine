#include "Scenes/RTSScene.h"
#include "Core/EntryPoint.h"
#include <vector>
class CraftRTS
{
public:
    ~CraftRTS()
    {
    };
    Engine engine;
    void StartGame()
    {
        // engine.SceneManager_.ChangeScene(new RogueScene());
        engine.scenes.push_back(new RTSScene());
        engine.StartGame();
    }
    void Clean()
    {
        engine.Clean();
    }
};

int main()
{
    CraftRTS *game = new CraftRTS();
    game->StartGame();
    game->Clean();
    delete game;
    system("pause");
    return 0;
}
