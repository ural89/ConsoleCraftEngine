#pragma once
#include <vector>
#include <memory>
#include <string>

enum class NodeStatus
{

    Inactive,
    Running,
    Success,
    Failure
};

class BehaviorTreeNode
{
public:
    BehaviorTreeNode(const std::string &&name) : name(name) {}
    BehaviorTreeNode(const std::string &name) : name(name) {}

protected:
    NodeStatus status;
    std::string name;

public:
    virtual ~BehaviorTreeNode() = default;

    virtual NodeStatus Update() = 0;

    NodeStatus getStatus() const { return status; }

    virtual std::string getName() const { return name; }
};
