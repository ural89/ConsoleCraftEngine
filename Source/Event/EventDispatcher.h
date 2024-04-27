#pragma once

#include "Event.h"

using EventListener = std::function<void(Event&)>;

class GE_API EventDispatcher
{
public: 
	static void AddListener(EventListener func);
	static void RemoveListener(EventListener func);

	static void CallEvent(Event& event);
};

