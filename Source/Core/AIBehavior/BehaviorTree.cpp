#include "BehaviorTree.h"

AIBehavior::BehaviorTree::BehaviorTree()
{
    m_Selector = std::make_unique<Selector>();
    m_SuccessNode = std::make_unique<SuccessNode>();
    m_Selector.get()->AddNodeChildNode(std::move(m_SuccessNode));
    m_RootNode.AddNodeChildNode(std::move(m_Selector));
}

AIBehavior::BehaviorTree::~BehaviorTree()
{
}

void AIBehavior::BehaviorTree::Update(float deltaTime)
{
    m_RootNode.Update(deltaTime);
}