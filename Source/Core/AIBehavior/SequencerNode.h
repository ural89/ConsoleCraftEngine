#pragma once

#include "NodeBase.h"
#include <vector>

namespace AIBehavior
{
    class SequencerNode : public NodeBase
    {
    public:
        SequencerNode() : NodeBase("Sequencer Node"), m_CurrentChildIndex(0) {}
        void Enter() override;
        void Exit() override;
        NodeResult Update(float deltaTime) override;

    private:
        int m_CurrentChildIndex; 
    };
}
