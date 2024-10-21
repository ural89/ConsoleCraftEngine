#pragma once

#include "NodeBase.h"
namespace AIBehavior
{
    class GoToTargetNode : public NodeBase
    {
    public:
        GoToTargetNode() : NodeBase("Go to target"){}
        
        void Enter() override;
        void Exit() override;
        NodeResult Update(float deltaTime) override;
    private:
        int m_DistanceToTarget = 5;
    };
};