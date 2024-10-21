#include "FailedNode.h"

using namespace AIBehavior;
NodeResult FailedNode::Update(float deltaTime)
{
    return NodeResult::Failed;
}

void FailedNode::Exit()
{
    NodeBase::Exit();
}

void FailedNode::Enter()
{
    NodeBase::Enter();
}
