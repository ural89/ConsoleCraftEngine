#pragma once
#include <memory>
#include "Pathfinder.h"
class AIMovement
{
public:
    AIMovement(std::shared_ptr<Pathfinder>& pathfinder) : m_Pathfinder(pathfinder)
    {

    }
private:
    std::shared_ptr<Pathfinder> m_Pathfinder;
};