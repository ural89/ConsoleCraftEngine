#include "Renderer.h"
#include "UIHandler.h"
#include "../CoreStructs/Vector.h"
#include <iostream>
Vector2 UIHandler::Position;
std::string UIHandler::uiText;
Renderer::Renderer()
{
    FixConsoleWindow();
    HideCursor();
}

void Renderer::Render(const Scene& scene)
{
    for (auto& go : scene.GetGameObjects())
    {

        if (!go->isRenderable) continue;
       
        if (go->transform.PreviousPosition != go->transform.Position)
        {
            if (go->isDestroyedFlag)
            {
                ClearDestroyedObject(*go);
                continue;
            }
            DrawObjects(*go);
            ClearMovedObjectsTrail(*go);
            DrawUI();
        }
    }
}

void Renderer::ClearDestroyedObject(GameObject& go)
{
    for (int i = 0; i < go.GetHeight() + 2; i++)
    {
        for (int j = 0; j < go.GetWidth() + 2; j++)
        {
            int posX = static_cast<int>(go.transform.Position.X + j - 1);
            int posY = static_cast<int>(go.transform.Position.Y + i - 1);

            GoToXY(posX, posY);
            std::cout << ' ';
        }
    }
    go.hasClearedFromScreen = true;
}

void Renderer::DrawObjects(GameObject& go)
{
    for (int i = 0; i < go.sprite.size(); i++) 
    {
        for (int j = 0; j < go.sprite[i].size(); j++)
        {
            int posX = static_cast<int>(go.transform.Position.X + j);
            int posY = static_cast<int>(go.transform.Position.Y + i);
            
            SetConsoleColor(go.sprite[i][j]);
            GoToXY(posX, posY);
            std::cout << go.symbol;
        }
    }
    SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
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

void Renderer::DrawUI()
{
    UIHandler::Position = Vector2(0, 29);
    
    GoToXY(UIHandler::Position.X, UIHandler::Position.Y);
    std::cout << UIHandler::uiText;
}

void Renderer::SetConsoleColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
