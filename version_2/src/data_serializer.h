#pragma once

#include "list_node.h"

#include <iostream>
#include <fstream>
#include <charconv>
#include <deque>
#include <unordered_map>
#include <forward_list>

#include <string_view>

struct DataFormat
{
    std::string data;
    int rand_index;
};

class DataSerializer
{
public:
    DataSerializer();

    // тут должны быть конструкторы/операторы копирования и присваивания

    ~DataSerializer();

    void read(const std::string &filename);

    void deserializeAndLoadList(ListNode *head);

    void serialize(const std::string &filename) const;

private:
    std::deque<DataFormat> readed_data_;
    std::unordered_map<ListNode *, int> node_to_index_;
    std::unordered_map<int, std::forward_list<ListNode *>> pending_rands_;

    ListNode *head_ = nullptr;
    ListNode *tail_ = nullptr;

    void clearHead() noexcept;
    void clearReaded() noexcept;
    int getIndex(ListNode *node) const;
};
