#pragma once

#include "list_node.h"

#include <deque>
#include <unordered_map>
#include <forward_list>
#include <string>
#include <sstream>

class DoubleLinkedList
{
public:
    DoubleLinkedList();
    virtual ~DoubleLinkedList();

    DoubleLinkedList(const DoubleLinkedList &) = delete;
    DoubleLinkedList &operator=(const DoubleLinkedList &) = delete;

    DoubleLinkedList(DoubleLinkedList &&other) noexcept;
    DoubleLinkedList &operator=(DoubleLinkedList &&other) noexcept;

    virtual void clear() noexcept;

    void push_back(std::string data);
    size_t size() const noexcept;

    void swap(DoubleLinkedList &other) noexcept;

protected:
    ListNode *head_ = nullptr;
    ListNode *tail_ = nullptr;
    size_t size_ = 0;

    static const size_t MAX_COUNT_NODES = 1000000;

    void clearImpl() noexcept;
};