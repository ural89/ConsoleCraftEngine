#pragma once
enum class EventType
{
	None = 0,
	WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
	AppTick, AppUpdate, AppRender,
	KeyPressed, KeyReleased,
	MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
};
class Event
{
public:
	Event(EventType eventType)
	{
		this->eventType = eventType;
	}

private:
	EventType eventType;
};

