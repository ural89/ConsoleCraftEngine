#pragma once
#include "../Core.h"
#include <functional>
#include <vector> 
const int SPACEBAR = 32;
const int KEY1 = 49;
const int KEY2 = 50;
const int KEY3 = 51;
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
    static std::vector<std::function<void(int)>> listeners;
};