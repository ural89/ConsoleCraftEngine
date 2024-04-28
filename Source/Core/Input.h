#pragma once
#include "../Core.h"
#include <functional>
#include <vector> 
const int SPACEBAR = 32;
const int KEY1 = 49;
const int KEY2 = 50;
const int KEY3 = 51;
#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)
class GE_API Input
{
public:
    Input();
    static void Update();
    static int GetKeyDown();  
    static void AddListener(std::function<void(int input)> func);
    static void RemoveListener(std::function<void(int input)> func);
    static void Cleanup()
    {
        listeners.clear();   
    }

   
   
private:
    
    static int keyDown;  
    static std::vector<std::function<void(int)>> listeners;
};