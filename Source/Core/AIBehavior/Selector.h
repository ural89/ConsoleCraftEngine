#pragma once
#include "NodeBase.h"
namespace AIBehavior
{
    class Selector : public NodeBase
    {
    public:
        void Enter() override;
        void Exit() override;
        NodeResult Update(float deltaTime) override;
    };
};