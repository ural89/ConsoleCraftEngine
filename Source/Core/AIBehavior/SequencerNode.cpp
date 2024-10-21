#include "SequencerNode.h"

using namespace AIBehavior;

void SequencerNode::Enter()
{
    m_CurrentChildIndex = 0; 
    if (!m_ChildNodes.empty())
    {
        m_ChildNodes[m_CurrentChildIndex]->Enter();  
    }
}

void SequencerNode::Exit()
{
    if (m_CurrentChildIndex < m_ChildNodes.size())
    {
        m_ChildNodes[m_CurrentChildIndex]->Exit();  
    }
}

NodeResult SequencerNode::Update(float deltaTime)
{
    if (m_ChildNodes.empty())
    {
        return NodeResult::Success;
    }

    while (m_CurrentChildIndex < m_ChildNodes.size())
    {
        NodeResult result = m_ChildNodes[m_CurrentChildIndex]->Update(deltaTime);

        if (result == NodeResult::Success)
        {
            m_ChildNodes[m_CurrentChildIndex]->Exit();
            m_CurrentChildIndex++;
            if (m_CurrentChildIndex < m_ChildNodes.size())
            {
                m_ChildNodes[m_CurrentChildIndex]->Enter();  
            }
        }
        else if (result == NodeResult::InProgress)
        {
            return NodeResult::InProgress;  
        }
        else if (result == NodeResult::Failed)
        {
            return NodeResult::Failed;  
        }
    }

    return NodeResult::Success;
}
