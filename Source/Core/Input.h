#pragma once
#include "../Core.h"
#include <functional>
#include <vector> //TODO: add this to core maybe
const int SPACEBAR = 32;
class GE_API Input
{
public:
    Input();
    static void Update();
    static int GetKeyDown();  // static
    static void AddListener(std::function<void(int input)> func);
    static void Cleanup()
    {
        // Clear the listeners vector
        listeners.clear();
        
    }

   
   
private:
    
    static int keyDown;  // static
    static std::vector<std::function<void(int)>> listeners;
};