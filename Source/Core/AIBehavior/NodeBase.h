#pragma once
#include <vector>
#include <memory>
#include <string>

enum class NodeStatus {

    Inactive,
    Running,
    Success,
    Failure
};

class BehaviorTreeNode {
protected:
    NodeStatus status;

public:
    virtual ~BehaviorTreeNode() = default;

    // Method to Update the node (run it)
    virtual NodeStatus Update() = 0;

    // Get the node status
    NodeStatus getStatus() const { return status; }
    
    // This can be useful for UI later
    virtual std::string getName() const = 0;
};
