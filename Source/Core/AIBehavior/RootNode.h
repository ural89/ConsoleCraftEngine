#pragma once
#include "NodeBase.h"

namespace AIBehavior
{
    class RootNode : public NodeBase
    {
        public:
            RootNode();
            void Enter() override;
            void Exit() override;
            NodeResult Update(float deltaTime) override;
    };
};