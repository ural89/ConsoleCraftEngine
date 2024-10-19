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
        virtual void Enter()
        {
            for (auto &childNode : m_ChildNodes)
            {
                childNode.get()->Enter();
            }
        }
        virtual void Exit()
        {
            for (auto &childNode : m_ChildNodes)
            {
                childNode.get()->Exit();
            }
        }
        virtual NodeResult Update(float deltaTime) = 0;

        void AddNodeChildNode(std::unique_ptr<NodeBase> childNode)
        {
            m_ChildNodes.push_back(std::move(childNode));
        }

    protected:
        std::vector<std::unique_ptr<NodeBase>> m_ChildNodes;
    
    //TODO: some kind of data should be enter here (like blackboard or u_int)
    };
    
};