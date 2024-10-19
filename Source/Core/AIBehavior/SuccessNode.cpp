#include "SuccessNode.h"

using namespace AIBehavior;
NodeResult SuccessNode::Update(float deltaTime)
{
    return NodeResult::Success;
}

void SuccessNode::Exit()
{
    NodeBase::Exit();
}

void SuccessNode::Enter()
{
    NodeBase::Enter();
}
