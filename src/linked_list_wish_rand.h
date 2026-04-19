#pragma once

#include "double_linked_list.h"
#include "rand_index_resolver.h"

#include <iostream>
#include <fstream>
#include <charconv>
#include <string_view>

class LinkedListWithRand : public DoubleLinkedList
{
public:
    using DoubleLinkedList::DoubleLinkedList;

    void deserialize(const std::string &filename);

    void serialize(const std::string &filename) const;

    void clear() noexcept override;

private:
    RandIndexResolver resolver;
};
