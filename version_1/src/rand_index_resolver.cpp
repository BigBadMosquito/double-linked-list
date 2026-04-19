#include "rand_index_resolver.h"

RandIndexResolver::RandIndexResolver() {};

void RandIndexResolver::registerNode(ListNode *node, int rand_index)
{
    int current_index = index_to_node_.size();
    index_to_node_.push_back(node);
    node_to_index_[node] = current_index;

    if (rand_index != -1)
    {
        if (rand_index < current_index)
        {
            node->rand = index_to_node_[rand_index];
        }
        else
        {
            registerPending(rand_index, node);
        }
    }

    resolvePending(current_index, node);
}

void RandIndexResolver::clear()
{
    index_to_node_.clear();
    pending_rands_.clear();
}

int RandIndexResolver::getIndex(ListNode *node) const
{
    auto it = node_to_index_.find(node);
    if (it != node_to_index_.end())
    {
        return it->second;
    }
    return -1;
}

void RandIndexResolver::registerPending(int target_index, ListNode *node)
{
    if (target_index >= 0)
    {
        pending_rands_[target_index].push_front(node);
    }
}

void RandIndexResolver::resolvePending(int created_index, ListNode *created_node)
{
    auto it = pending_rands_.find(created_index);
    if (it != pending_rands_.end())
    {
        for (ListNode *waiting_node : it->second)
        {
            waiting_node->rand = created_node;
        }
        pending_rands_.erase(it);
    }
}