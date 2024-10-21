#pragma once

#include "NodeBase.h"
namespace AIBehavior
{
    class WaitNode : public NodeBase
    {
    public:
        WaitNode(int waitTime) : NodeBase("Wait Node"), m_WaitTime(waitTime) {}
        NodeResult Update(float deltaTime);
        void Enter() override;
        void Exit() override;
    private:
        int m_WaitTime;
    };
};