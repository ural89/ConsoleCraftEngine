#include "Renderer.h"

Renderer::Renderer()
{
    FixConsoleWindow();
    HideCursor();
}

void Renderer::Render(const Scene& scene)
{
    for (auto& go : scene.GetGameObjects())
    {
        if (go->transform.PreviousPosition != go->transform.Position)
        {
            if (go->isDestroyedFlag)
            {
                ClearDestroyedObject(*go);
                continue;
            }
            DrawObjects(*go);
            ClearMovedObjectsTrail(*go);
        }
    }
}

void Renderer::ClearDestroyedObject(GameObject& go)
{
    for (int i = 0; i < go.sprite.size(); i++)
    {
        for (int j = 0; j < go.sprite[i].size() + 2; j++)
        {
            int posX = static_cast<int>(go.transform.Position.X + j - 1);
            int posY = static_cast<int>(go.transform.Position.Y + i);

            GoToXY(posX, posY);
            std::cout << ' ';
        }
    }
    go.hasClearedFromScreen = true;
}

void Renderer::DrawObjects(GameObject& go)
{
    for (int i = 0; i < go.sprite.size(); i++) //TODO: Find better matrix system
    {
        for (int j = 0; j < go.sprite[i].size(); j++)
        {
            int posX = static_cast<int>(go.transform.Position.X + j);
            int posY = static_cast<int>(go.transform.Position.Y + i);

            GoToXY(posX, posY);
            std::cout << go.symbol;
        }
    }
}

void Renderer::ClearMovedObjectsTrail(GameObject& go)
{
    if (!go.transform.HasClearedFlag)
    {
        // Clear previous image of sprite
        for (int i = 0; i < go.sprite.size(); i++)
        {
            for (int j = 0; j < go.sprite[i].size(); j++)
            {
                int clearX = static_cast<int>(go.transform.PreviousPosition.X + j);
                int clearY = static_cast<int>(go.transform.PreviousPosition.Y + i);

                GoToXY(clearX, clearY);
                std::cout << ' ';
            }
        }

        go.transform.HasClearedFlag = true;
    }
}