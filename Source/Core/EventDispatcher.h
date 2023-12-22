#pragma once
#include "../Core.h"
#include <vector>
#include <functional>
#include "Event.h"
class GE_API EventDispatcher
{
public: 
	static void AddListener(std::function<void(Event&)> func);
	static void RemoveListener(std::function<void(Event&)> func);
	static void CallEvent(Event& event);
private:
	
};

