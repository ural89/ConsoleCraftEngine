#include "Scenes/CraftCityScene.h"
#include "Scenes/CraftCityMainMenuScene.h"
#include "Core/EntryPoint.h"
#include <vector>
class CraftCity
{
public:
    ~CraftCity()
    {
    };
    Engine engine;
    void StartGame()
    {
        engine.scenes.push_back(new CraftCityScene());
        engine.scenes.push_back(new CraftCityMainMenuScene());
        engine.StartGame();
    }
    void Clean()
    {
        engine.Clean();
    }
};

int main()
{
    CraftCity* game = new CraftCity();
    game->StartGame();
    game->Clean();
    delete game;
    system("pause");
    return 0;
}
