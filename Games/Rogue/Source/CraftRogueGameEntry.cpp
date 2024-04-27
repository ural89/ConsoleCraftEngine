#include "Scenes/RogueScene.h"
#include "Main/Engine.h"

class CraftRogue
{
public:
    ~CraftRogue()
    {
    };
    Engine engine;
    void StartGame()
    {
        engine.scenes.push_back(new RogueScene());
        engine.StartGame();
    }
    void Clean()
    {
        engine.Clean();
    }
};

int main()
{
    CraftRogue *game = new CraftRogue();
    game->StartGame();
    game->Clean();
    delete game;
    system("pause");
    return 0;
}
