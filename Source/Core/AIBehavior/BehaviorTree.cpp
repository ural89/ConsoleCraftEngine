#include "NodeBase.h"
#include "CompositeNode.h"
#include "ActionNode.h"
#include "BehaviorTree.h"

BehaviorTree::BehaviorTree(std::shared_ptr<BehaviorTreeNode> _root) : root(_root)
{
    
}
