#include "EventDispatcher.h"

static std::vector<EventListener> listeners;

void EventDispatcher::AddListener(EventListener func)
{
    listeners.push_back(func);
}

void EventDispatcher::RemoveListener(EventListener func)
{
    auto it = std::remove_if(listeners.begin(), listeners.end(),
        [&func](const std::function<void(Event&)>& listener) {
            return listener.target<void(Event&)>() == func.target<void(Event&)>();
        });

    listeners.erase(it, listeners.end());
}

void EventDispatcher::CallEvent(Event& event)
{
    for (auto& listener : listeners)
    {
        listener(event);
    }
}
