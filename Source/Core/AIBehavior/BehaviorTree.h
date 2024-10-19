#pragma once

#include "NodeBase.h"
#include "Selector.h"
#include "SuccessNode.h"
#include "RootNode.h"

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
            Selector m_Selector;
            SuccessNode m_SuccessNode;
    };
};