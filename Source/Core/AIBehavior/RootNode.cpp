#include "RootNode.h"
using namespace AIBehavior;
void RootNode::Enter()
{
    NodeBase::Enter();
}
void RootNode::Exit()
{
    NodeBase::Exit();
}
NodeResult RootNode::Update(float deltaTime)
{

    for (auto &childNode : m_ChildNodes)//root node can get 1 child only?
    {
        childNode.get()->Update(deltaTime);
    }
}