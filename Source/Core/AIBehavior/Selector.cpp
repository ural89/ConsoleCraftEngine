#include "Selector.h"
#include <iostream>

using namespace AIBehavior;

void SelectorNode::Enter()
{
    m_CurrentChildIndex = 0;

    if (!m_ChildNodes.empty())
    {
        m_ChildNodes[m_CurrentChildIndex]->Enter();
    }
}

void SelectorNode::Exit()
{
    if (!m_ChildNodes.empty())
    {
        m_ChildNodes[m_CurrentChildIndex]->Exit();
    }
}

NodeResult SelectorNode::Update(float deltaTime)
{
    while (m_CurrentChildIndex < m_ChildNodes.size())
    {
        NodeResult childNodeResult = m_ChildNodes[m_CurrentChildIndex]->Update(deltaTime);

        if (childNodeResult == NodeResult::InProgress)
        {
            std::cout << nodeName << " In Progress: " << m_ChildNodes[m_CurrentChildIndex]->nodeName << '\n';
            return NodeResult::InProgress;
        }
        else if (childNodeResult == NodeResult::Success)
        {
            std::cout << nodeName << " Succeeded: " << m_ChildNodes[m_CurrentChildIndex]->nodeName << '\n';
            return NodeResult::Success;
        }

        m_CurrentChildIndex++;
    }

    std::cout << nodeName << " Failed\n";
    return NodeResult::Failed;
}
