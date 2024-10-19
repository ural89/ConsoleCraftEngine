#pragma once
#include <vector>
#include <memory>
namespace AIBehavior
{
    enum NodeResult
    {
        Success,
        InProgress,
        Failed
    };
    class NodeBase
    {
    public:
        int test = 10;
        virtual void Enter() = 0;
        virtual void Exit() = 0;
        virtual NodeResult Update(float deltaTime) = 0;

        void AddNodeChildNode(std::unique_ptr<NodeBase> childNode)
        {
            m_ChildNodes.push_back(std::move(childNode));
        }

    protected:
        std::vector<std::unique_ptr<NodeBase>> m_ChildNodes;
    };

};