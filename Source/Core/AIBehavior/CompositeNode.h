#pragma once
#include "NodeBase.h"
class CompositeNode : public BehaviorTreeNode
{
protected:
public:
    CompositeNode(const std::string &name) : BehaviorTreeNode(name) {}
    std::vector<std::shared_ptr<BehaviorTreeNode>> children;
    void addChild(std::shared_ptr<BehaviorTreeNode> child)
    {
        children.push_back(child);
    }
};

class SequenceNode : public CompositeNode
{
public:
    SequenceNode(const std::string &name) : CompositeNode(name) {}
    NodeStatus Update() override
    {
        status = NodeStatus::Running;
        for (auto &child : children)
        {
            NodeStatus childStatus = child->Update();
            if (childStatus != NodeStatus::Success)
            {
                status = childStatus;
                return status;
            }
        }
        status = NodeStatus::Success;
        return status;
    }
};

class SelectorNode : public CompositeNode
{
public:
    SelectorNode(const std::string& name) : CompositeNode(name){}
    NodeStatus Update() override
    {
        status = NodeStatus::Running;
        for (auto &child : children)
        {
            NodeStatus childStatus = child->Update();
            if (childStatus != NodeStatus::Failure)
            {
                status = childStatus;
                return status;
            }
        }
        status = NodeStatus::Failure;
        return status;
    }
};
