#pragma once

namespace AIBehavior
{
    class NodeBase
    {
    public:
        virtual NodeResult Update(float deltaTime) = 0;
    };

    enum NodeResult
    {
        Success,
        InProgress,
        Failed
    };
};