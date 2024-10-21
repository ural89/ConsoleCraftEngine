#pragma once

#include "NodeBase.h"
namespace AIBehavior
{
    class InProgressNode : public NodeBase
    {
    public:
        InProgressNode() : NodeBase("In Progress Node"){}
        NodeResult Update(float deltaTime);
        void Enter() override;
        void Exit() override;
    };
};