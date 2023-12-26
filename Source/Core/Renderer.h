#pragma once
#include "../Core.h"
#include "Scene.h"
// #include <Windows.h>
class GE_API Renderer
{
public:
    Renderer();
    void Render(const Scene& scene);
private:

    void FixConsoleWindow()
    {
        // HWND consoleWindow = GetConsoleWindow();
        // LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
        // style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
        // SetWindowLong(consoleWindow, GWL_STYLE, style);
    }
    void GoToXY(int x, int y)
    {
        // COORD coord;
        // coord.X = x;
        // coord.Y = y;
        // SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }
    void HideCursor()
    {
        // HANDLE fd = GetStdHandle(STD_OUTPUT_HANDLE);
        // CONSOLE_CURSOR_INFO cinfo;
        // cinfo.bVisible = 0;
        // cinfo.dwSize = 1;
        // SetConsoleCursorInfo(fd, &cinfo);
    }

    void ClearDestroyedObject(GameObject& go);
    void DrawObjects(GameObject& go);
    void ClearMovedObjectsTrail(GameObject& go);
    void DrawUI();
    void SetConsoleColor(int color);
	
};

