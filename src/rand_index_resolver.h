#pragma once

#include "list_node.h"

#include <deque>
#include <unordered_map>
#include <forward_list>

class RandIndexResolver
{
public:
    RandIndexResolver();

    void registerNode(ListNode *node, int rand_index);

    int getIndex(ListNode *node) const;

    size_t getPendingCount() const { return pending_rands.size(); }
    size_t getNodeCount() const { return index_to_node.size(); }

    void clear();

private:
    std::deque<ListNode *> index_to_node;
    std::unordered_map<ListNode*, int> node_to_index;  
    std::unordered_map<int, std::forward_list<ListNode *>> pending_rands;

    void registerPending(int target_index, ListNode *source);
    void resolvePending(int created_index, ListNode *created_node);
};