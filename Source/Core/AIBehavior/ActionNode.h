#pragma once
#include "NodeBase.h"

class ActionNode : public BehaviorTreeNode {
public:
    ActionNode(const std::string &name) : BehaviorTreeNode(name){}
    NodeStatus Update() override {
        // Define the specific action here
        status = NodeStatus::Success; // or Failure or Running depending on the action
        return status;
    }
};

class FailNode : public BehaviorTreeNode {
public:
    FailNode(const std::string &name) : BehaviorTreeNode(name){}
    NodeStatus Update() override {
        // Define the specific action here
        status = NodeStatus::Failure; // or Failure or Running depending on the action
        return status;
    }

};

class ConditionNode : public BehaviorTreeNode {
public:
    ConditionNode(const std::string &name) : BehaviorTreeNode(name) {}
    NodeStatus Update() override {
        // Define the specific condition check here
        status = NodeStatus::Success; // or Failure depending on the condition
        return status;
    }

};
