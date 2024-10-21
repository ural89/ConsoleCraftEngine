#include "BehaviorTree.h"
#include "GoToTargetNode.h"
#include "SequencerNode.h"
#include "WaitNode.h"

AIBehavior::BehaviorTree::BehaviorTree()
{
    m_Selector = std::make_unique<SelectorNode>();
    m_SuccessNode = std::make_unique<SuccessNode>();
    m_FailedNode = std::make_unique<FailedNode>();
    m_InProgressNode = std::make_unique<InProgressNode>();

    auto waitNode = std::make_unique<WaitNode>(3);
    auto sequencerNode = std::make_unique<SequencerNode>();
    auto childSelector = std::make_unique<SelectorNode>("Child Selector");
    auto goToTargetNode = std::make_unique<GoToTargetNode>();

    sequencerNode->AddNodeChildNode(std::move(waitNode));
    sequencerNode->AddNodeChildNode(std::move(goToTargetNode));
    m_Selector->AddNodeChildNode(std::move(sequencerNode));
    m_RootNode.AddNodeChildNode(std::move(m_Selector));

    //TODO: create practicle way to add nodes like alias or smt
}

AIBehavior::BehaviorTree::~BehaviorTree()
{
}

void AIBehavior::BehaviorTree::Update(float deltaTime)
{
    m_RootNode.Update(deltaTime);
}