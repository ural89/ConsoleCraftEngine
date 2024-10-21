#include "RootNode.h"
#include <iostream>

using namespace AIBehavior;

AIBehavior::RootNode::RootNode() : NodeBase("RootNode")
{
}

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
            std::string result = nodeResult==InProgress? "InProgress" : "Success";
            std::cout << "Root node result is " << result << '\n';
            return nodeResult;
        }
    }

    std::cout << "Root node result is failed" << '\n';
    return NodeResult::Failed;
}