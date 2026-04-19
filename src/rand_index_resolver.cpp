#include "rand_index_resolver.h"

RandIndexResolver::RandIndexResolver() {};

void RandIndexResolver::registerNode(ListNode *node, int rand_index)
{
    int current_index = index_to_node.size();
    index_to_node.push_back(node);
    node_to_index[node] = current_index;

    if (rand_index != -1)
    {
        if (rand_index < current_index)
        {
            node->rand = index_to_node[rand_index];
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
    index_to_node.clear();
    pending_rands.clear();
}

int RandIndexResolver::getIndex(ListNode *node) const
{
    auto it = node_to_index.find(node);
    if (it != node_to_index.end())
    {
        return it->second;
    }
    return -1;
}

void RandIndexResolver::registerPending(int target_index, ListNode *source)
{
    if (target_index >= 0)
    {
        pending_rands[target_index].push_front(source);
    }
}

void RandIndexResolver::resolvePending(int created_index, ListNode *created_node)
{
    auto it = pending_rands.find(created_index);
    if (it != pending_rands.end())
    {
        for (ListNode *waiting_node : it->second)
        {
            waiting_node->rand = created_node;
        }
        pending_rands.erase(it);
    }
}