#include "Scenes/DefenseScene.h"
#include "Core/EntryPoint.h"
#include <vector>

class CraftDefense
{
public:
    ~CraftDefense()
    {
    };

    Engine engine;

    void StartGame()
    {
        engine.scenes.push_back(new DefenseScene());
        engine.StartGame();
    }

    void Clean()
    {
        engine.Clean();
    }
};

int main()
{
    CraftDefense *game = new CraftDefense();
    game->StartGame();
    game->Clean();
    delete game;
    system("pause");
    return 0;
}
