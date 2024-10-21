#include "GoToTargetNode.h"
#include <iostream>

using namespace AIBehavior;
void AIBehavior::GoToTargetNode::Enter()
{
    m_DistanceToTarget = 5;
}
void AIBehavior::GoToTargetNode::Exit()
{
}
NodeResult GoToTargetNode::Update(float deltaTime)
{
    m_DistanceToTarget -= deltaTime;
    std::cout << "Going to target: " << m_DistanceToTarget << '\n';
    if(m_DistanceToTarget <= 0)
    {
        return NodeResult::Success;
    }
    return NodeResult::InProgress;
}