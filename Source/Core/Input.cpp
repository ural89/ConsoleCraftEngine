#include <conio.h>
#include "Input.h"
#include <iostream>

int Input::keyDown = 0;  // Initialize the static member variable

Input::Input() {}
std::vector<std::function<void(int)>> Input::listeners;
void Input::Update()
{
    if (_kbhit())
    {
        keyDown = _getch();
       
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
    //auto newEnd = std::remove(listeners.begin(), listeners.end(), func); //Move element to last
    //listeners.erase(newEnd, listeners.end()); //erase last one
}
