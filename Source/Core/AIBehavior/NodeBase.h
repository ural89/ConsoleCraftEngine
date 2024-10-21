#pragma once
#include <vector>
#include <memory>
#include <string>
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
        NodeBase(std::string nodeName) : nodeName(nodeName){}
        virtual ~NodeBase()
        {
            m_ChildNodes.clear();
        }
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
            childNode->SetParentNode(this);
            m_ChildNodes.push_back(std::move(childNode));
        }

        void SetParentNode(NodeBase *parentNode)
        {
            m_ParentNode = parentNode;
        }

    public:
        std::string nodeName = "Node";

    protected:
        std::vector<std::unique_ptr<NodeBase>> m_ChildNodes;

    private:
        NodeBase *m_ParentNode;

        // TODO: some kind of data should be enter here (like blackboard or u_int)
    };

};