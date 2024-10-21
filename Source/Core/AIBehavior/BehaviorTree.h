#pragma once

#include "NodeBase.h"
#include "Selector.h"
#include "SuccessNode.h"
#include "FailedNode.h"
#include "InProgressNode.h"
#include "RootNode.h"

#include <memory>

namespace AIBehavior
{
    class BehaviorTree
    {
    public:
        BehaviorTree();
        ~BehaviorTree();
        void Update(float deltaTime);

    private:
        RootNode m_RootNode;
        std::unique_ptr<SelectorNode> m_Selector;
        std::unique_ptr<SuccessNode> m_SuccessNode;
        std::unique_ptr<FailedNode> m_FailedNode;
        std::unique_ptr<InProgressNode> m_InProgressNode;
    };
};