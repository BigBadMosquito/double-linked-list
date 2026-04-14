#pragma once

#include "list_node.h"

class DoubleLinkedList {
public:
    DoubleLinkedList();

    ~DoubleLinkedList();

    void Clear() noexcept;

private:
    ListNode* head_ = nullptr;

};