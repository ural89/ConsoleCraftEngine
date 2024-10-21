#pragma once

#include "NodeBase.h"
namespace AIBehavior
{
    class FailedNode : public NodeBase
    {
    public:
        FailedNode() : NodeBase("Fail Node") {}
        NodeResult Update(float deltaTime) override;
        void Enter() override;
        void Exit() override;
    };
};