#include "RootNode.h"
#include <iostream>

using namespace AIBehavior;

void RootNode::Enter()
{
}
void RootNode::Exit()
{
}
NodeResult RootNode::Update(float deltaTime)
{

    for (auto &childNode : m_ChildNodes) // root node can get 1 child only?
    {
        auto nodeResult = childNode.get()->Update(deltaTime);
        if (nodeResult == NodeResult::InProgress || nodeResult == NodeResult::Success)
        {
            std::cout << "Root node result is " << nodeResult << '\n';
            return nodeResult;
        }
    }

    std::cout << "Root node result is failed" << '\n';
    return NodeResult::Failed;
}