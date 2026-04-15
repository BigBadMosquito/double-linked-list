#pragma once

#include "list_node.h"

class DoubleLinkedList {
public:
    DoubleLinkedList();
    ~DoubleLinkedList();

    DoubleLinkedList(const DoubleLinkedList&) = delete;
    DoubleLinkedList& operator=(const DoubleLinkedList&) = delete;
    
    DoubleLinkedList(DoubleLinkedList&& other) noexcept;
    DoubleLinkedList& operator=(DoubleLinkedList&& other) noexcept;

    void Clear() noexcept;

    // void PushBack(std::string data, int rand_index);

    void swap(DoubleLinkedList & other) noexcept ;
private:
    ListNode* head_ = nullptr;

};