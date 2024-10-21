#include "InProgressNode.h"

using namespace AIBehavior;
NodeResult InProgressNode::Update(float deltaTime)
{
    return NodeResult::InProgress;
}

void InProgressNode::Exit()
{
    NodeBase::Exit();
}

void InProgressNode::Enter()
{
    NodeBase::Enter();
}
