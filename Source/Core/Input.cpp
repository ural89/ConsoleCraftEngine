#ifdef __GNUC__
#include "../l_conio.h"
#else
#include <conio.h>
#endif
#include "Input.h"
#include <iostream>
#include <algorithm>
int Input::keyDown = 0;  // Initialize the static member variable

Input::Input() {}

void Input::Update()
{
#ifdef __GNUC__
    if (kbhit())
#else
    if(_kbhit())
#endif
    {
    #ifdef __GNUC__
        keyDown = getch();
    #else
        keyDown = _getch();
    #endif
       
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
    auto it = std::remove_if(listeners.begin(), listeners.end(),
        [func](const auto& listener) {
            return listener.target_type() == func.target_type();
        });
    listeners.erase(it, listeners.end());
}


