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
            DrawUI();
            DrawObjects(*go);
            ClearMovedObjectsTrail(*go);
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
            
            int color = go.sprite[i][j];
            if (go.overrideColor >= 0 && color != 0)
                SetConsoleColor(go.overrideColor);
            else
            {
                if (color == 0 || (posX> SCREENWIDTH)|| (posY > SCREENHEIGHT))
                {
                    continue;
                }
                SetConsoleColor(color);
            }
            GoToXY(posX, posY);
            std::cout << go.symbol;
        }
    }
     SetConsoleColor(15);
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
                if ((clearX> SCREENWIDTH)|| (clearY > SCREENHEIGHT))
                {
                    continue;
                }

                GoToXY(clearX, clearY);
                std::cout << ' ';
            }
        }

        go.transform.HasClearedFlag = true;
    }
}

void Renderer::DrawUI()
{
    GoToXY(UIHandler::Position.X, UIHandler::Position.Y);
    std::cout << UIHandler::uiText;
}

void Renderer::SetConsoleColor(int color)
{
    std::cout << "\033[38;5;" << color << "m";
}

std::vector<std::vector<int>> Renderer::RotateSprite(const std::vector<std::vector<int>> &sprite)
{
    int rows = sprite.size();
    int cols = sprite[0].size();

 
    std::vector<std::vector<int>> rotated(cols, std::vector<int>(rows, 0));

   
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            rotated[j][rows - 1 - i] = sprite[i][j];
        }
    }

    return rotated;
}
