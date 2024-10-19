#include "Selector.h"
#include <iostream>
using namespace AIBehavior;

void Selector::Exit()
{
}
void Selector::Enter()
{
}
NodeResult Selector::Update(float deltaTime)
{
    for (auto &node : m_ChildNodes)
    {
        auto childNodeResult = node.get()->Update(deltaTime);
        if (childNodeResult == NodeResult::InProgress)
        {
            std::cout << "Node In Progress \n";
            return NodeResult::InProgress;
        }
        else if (childNodeResult == NodeResult::Success)
        {
            std::cout << "Node Succeeded\n";
            return NodeResult::Success;
        }
    }
    return NodeResult::Failed;
}
