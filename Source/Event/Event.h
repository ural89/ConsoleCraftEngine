#pragma once

#include "Core/Typedefs.h"

enum class EventType
{
	None = 0,
	OnEnemySpawned = 1,
	OnEnemyKilled = 2,
};

// @TODO: This class does serves no purpose
class Event
{
public:
	Event(EventType eventType)
	{
		this->eventType = eventType;
	}
	EventType GetEventType() const
	{
		return eventType;
	}

private:
	EventType eventType;
};

