#include "../conio.h"
#include "Input.h"
#include <iostream>
#include <algorithm>
int Input::keyDown = 0;  // Initialize the static member variable

Input::Input() {}
std::vector<std::function<void(int)>> Input::listeners;
void Input::Update()
{
    if (kbhit())
    {
        keyDown = getch();
       
        for (auto &listener:listeners)
        {
            listener(keyDown);
        }
    }
    else
    {
        keyDown = 0;
    }
}

int Input::GetKeyDown()
{
    return keyDown;
}

void Input::AddListener(std::function<void(int input)> func)
{
    listeners.push_back(func);
}

void Input::RemoveListener(std::function<void(int input)> func)
{
    listeners.erase(std::remove_if(listeners.begin(), listeners.end(),
                                   [&func](const std::function<void(int input)>& listener) {
                                       return listener.target<void(int input)>() == func.target<void(int input)>();
                                   }),
                    listeners.end());
}
