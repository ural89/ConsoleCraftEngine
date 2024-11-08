#pragma once
#include "NodeBase.h"

class ActionNode : public BehaviorTreeNode {
    std::string name;
public:
    ActionNode(const std::string& name) : name(name) {}

    NodeStatus Update() override {
        // Define the specific action here
        status = NodeStatus::Success; // or Failure or Running depending on the action
        return status;
    }

    std::string getName() const override { return name; }
};

class FailNode : public BehaviorTreeNode {
    std::string name;
public:
    FailNode(const std::string& name) : name(name) {}

    NodeStatus Update() override {
        // Define the specific action here
        status = NodeStatus::Failure; // or Failure or Running depending on the action
        return status;
    }

    std::string getName() const override { return name; }
};

class ConditionNode : public BehaviorTreeNode {
    std::string name;
public:
    ConditionNode(const std::string& name) : name(name) {}

    NodeStatus Update() override {
        // Define the specific condition check here
        status = NodeStatus::Success; // or Failure depending on the condition
        return status;
    }

    std::string getName() const override { return name; }
};
