#pragma once

#include "Core/Typedefs.h"

const int SPACEBAR = 32;
const int KEY1 = 49;
const int KEY2 = 50;
const int KEY3 = 51;

using InputListener = std::function<void(int)>;

class GE_API Input
{
public:
    Input();
    static void Update();
    static int GetKeyDown();  // static
    static void AddListener(std::function<void(int input)> func);
    static void RemoveListener(std::function<void(int input)> func);
    static void Cleanup()
    {
        // Clear the listeners vector
        listeners.clear();        
    }

   
   
private:    
    static int keyDown;  // static
    static inline std::vector<InputListener> listeners; // Craig: Added inline due to error LNK2001: unresolved external symbol 
};