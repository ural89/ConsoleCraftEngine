#include "Renderer.h"
#include "UIHandler.h"
#include "../CoreStructs/Vector.h"
#include <iostream>
#include <vector>
struct UIData;

Renderer::Renderer()
{
    FixConsoleWindow();
    HideCursor();
}

void Renderer::Render(Scene &scene)
{
    for (auto &go : scene.GetGameObjects())
    {

      //  if (go->transform.HasMovedThisFrame)
        {
            if (go->isRenderable)
                DrawObjects(*go, scene);

            ClearMovedObjectsTrail(*go, scene);
            ClearObjectTrailAfterCameraMove(*go, scene);
            if (go->isDestroyedFlag || go->forceClearFromScreen)
            {
                ClearDestroyedObject(*go, scene);
                go->forceClearFromScreen = false;
                continue;
            }
        }
    }
    DrawUI(scene);
    scene.camera->HasMovedDirection = 0;
}

void Renderer::ClearDestroyedObject(GameObject &go, Scene &scene)
{
    for (int i = 0; i < go.GetHeight() + 2; i++)
    {
        for (int j = 0; j < go.GetWidth() + 2; j++)
        {
            int posX = static_cast<int>(go.transform.Position.X + j - 1) + scene.camera->offsetX;
            int posY = static_cast<int>(go.transform.Position.Y + i - 1) + scene.camera->offsetY;

            GoToXY(posX, posY);
            std::cout << ' ';
        }
    }
    go.hasClearedFromScreen = true;
}

void Renderer::DrawObjects(GameObject &go, Scene &scene)
{
    for (int i = 0; i < go.sprite.size(); i++)
    {
        for (int j = 0; j < go.sprite[i].size(); j++)
        {
            int posX = static_cast<int>(go.transform.Position.X + j) + scene.camera->offsetX;
            int posY = static_cast<int>(go.transform.Position.Y + i) + scene.camera->offsetY;

            int color = go.sprite[i][j];
            if (go.overrideColor >= 0 && color != 0)
                SetConsoleColor(go.overrideColor);
            else
            {
                if (color == 0 || (posX > SCREENWIDTH) || (posY > SCREENHEIGHT) || (posY < 0) || (posX < 0))
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

void Renderer::ClearMovedObjectsTrail(GameObject &go, Scene &scene)
{
    if (!go.transform.HasClearedFlag)
    {
        // Clear previous image of sprite
        for (int i = 0; i < go.sprite.size(); i++)
        {
            for (int j = 0; j < go.sprite[i].size(); j++)
            {
                int clearX = static_cast<int>(go.transform.PreviousPosition.X + j) + scene.camera->offsetX;
                int clearY = static_cast<int>(go.transform.PreviousPosition.Y + i) + scene.camera->offsetY;
                if ((clearX > SCREENWIDTH) || (clearY > SCREENHEIGHT) || ((clearX < 0) || (clearY < 0)))
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

void Renderer::ClearObjectTrailAfterCameraMove(GameObject &go, Scene &scene)
{
    if (scene.camera->HasMovedDirection > 0)
    {
        int clearXOffset = 0;
        int clearYOffset = 0;
        switch (scene.camera->HasMovedDirection)
        {
        case UPDIRECTION:
            clearYOffset = 1;
            clearXOffset = 0;
            break;
        case RIGHTDIRECTION:
            clearYOffset = 0;
            clearXOffset = 1;
            break;
        case DOWNDIRECTION:
            clearYOffset = -1;
            clearXOffset = 0;
            break;
        case LEFTDIRECTION:
            clearYOffset = 0;
            clearXOffset = -1;
            break;
        }
        for (int i = 0; i < go.sprite.size(); i++)
        {
            for (int j = 0; j < go.sprite[i].size(); j++)
            {
                int clearX = static_cast<int>(go.transform.Position.X + j) + scene.camera->offsetX + clearXOffset;
                int clearY = static_cast<int>(go.transform.Position.Y + i) + scene.camera->offsetY + clearYOffset;
                if ((clearX > SCREENWIDTH) || (clearY > SCREENHEIGHT) || ((clearX < 0) || (clearY < 0)))
                {
                    continue;
                }

                GoToXY(clearX, clearY);
                std::cout << ' ';
            }
        }
    }
}

void Renderer::DrawUI(const Scene &scene)
{
    for (const auto &uiData : scene.uiHandler->uiDatas) // erase
    {
        GoToXY(uiData->position.X, uiData->position.Y);
        std::string s(uiData->text.size() + 1, ' ');
        std::cout << s;
    }
    for (auto &panel : scene.uiHandler->uiPanels)
    {
        if (panel->isActive)
        {
            for (auto &uiData : panel->uiDatas)
            {
                if (uiData->isActive)
                {
                    GoToXY(uiData->position.X, uiData->position.Y);
                    std::cout << uiData->text;
                }
            }
        }
        if (!panel->hasClearedFlag)
        {
            panel->hasClearedFlag = true;
            for (auto &uiData : panel->uiDatas)
            {

                GoToXY(uiData->position.X, uiData->position.Y);
                std::string s(uiData->text.size() + 40, ' ');
                std::cout << s;
            }
        }
    }
    for (auto &uiData : scene.uiHandler->uiDatas)
    {
        if (uiData->isActive)
        {
            GoToXY(uiData->position.X, uiData->position.Y);
            std::cout << uiData->text;
        }
    }
}

void Renderer::SetConsoleColor(int color)
{
#ifdef __GNUC__
    std::cout << "\033[38;5;" << color << "m";
#else
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
#endif
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
