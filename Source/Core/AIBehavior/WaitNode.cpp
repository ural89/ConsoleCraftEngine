#include "WaitNode.h"
#include <iostream>
using namespace AIBehavior;
NodeResult AIBehavior::WaitNode::Update(float deltaTime)
{
    m_WaitTime -= deltaTime;
    std::cout << "Waiting " << m_WaitTime << '\n';
    if(m_WaitTime <= 0)
    {
        return NodeResult::Success;
    }
    return NodeResult::InProgress; 
}

void AIBehavior::WaitNode::Enter()
{
}

void AIBehavior::WaitNode::Exit()
{
}
