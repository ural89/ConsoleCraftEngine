#pragma once
#include "../Core.h"
#include "Scene.h"
#include "ncurses.h"
// #include <Windows.h>
class GE_API Renderer
{
public:
    Renderer();
    void Render(const Scene& scene);

    static std::vector<std::vector<int>> RotateSprite(const std::vector<std::vector<int>>& sprite);
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
        #ifdef __GNUC__
        
          std::cout << "\033[" << y << ";" << x << "H";
    #else
        
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    #endif
    }
    void HideCursor()
    {
        curs_set(0);
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

