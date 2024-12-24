#include "EventDispatcher.h"
#include <algorithm> 
std::vector<std::function<void(Event&)>> listeners;

void EventDispatcher::AddListener(std::function<void(Event&)>& func)
{
    listeners.push_back(func);
}
void EventDispatcher::RemoveListener(std::function<void(Event&)> func) 
{
    auto it = std::remove_if(listeners.begin(), listeners.end(),
        [func](const auto& listener) {
            return listener.target_type() == func.target_type();
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
