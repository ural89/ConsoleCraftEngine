#pragma once

#include "CompositeNode.h"
#include <iostream>
class BehaviorTree {
    std::shared_ptr<BehaviorTreeNode> root;

public:
    BehaviorTree(std::shared_ptr<BehaviorTreeNode> root);

    void Update() {
        root->Update();
        printTreeStatus(root);
    }

    void printTreeStatus(std::shared_ptr<BehaviorTreeNode> node, int depth = 0) const {
        std::string indent(depth * 2, ' ');

        std::cout << indent << node->getName() << ": " << toString(node->getStatus()) << "\n";

        auto composite = std::dynamic_pointer_cast<CompositeNode>(node);
        if (composite) {
            for (const auto& child : composite->children) {
                printTreeStatus(child, depth + 1);
            }
        }
    }

private:
    std::string toString(NodeStatus status) const {
        switch (status) {
            case NodeStatus::Inactive: return "Inactive";
            case NodeStatus::Running: return "Running";
            case NodeStatus::Success: return "Success";
            case NodeStatus::Failure: return "Failure";
        }
        return "Unknown";
    }
};
