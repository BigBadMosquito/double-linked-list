#include "double_linked_list.h"

DoubleLinkedList::DoubleLinkedList() : head_(new ListNode)
{
}

DoubleLinkedList::~DoubleLinkedList()
{
    clear();
}

DoubleLinkedList::DoubleLinkedList(DoubleLinkedList &&other) noexcept : head_(std::move(other.head_)) {}

DoubleLinkedList &DoubleLinkedList::operator=(DoubleLinkedList &&other) noexcept
{
    DoubleLinkedList tpm(std::move(other));
    this->swap(tpm);
    return *this;
}

void DoubleLinkedList::clear() noexcept
{
    clearImpl();
}

void DoubleLinkedList::clearImpl() noexcept
{
    while (head_->next)
    {
        auto node = head_->next;
        head_->next = head_->next->next;
        delete node;
    }

    tail_ = nullptr;
    delete head_;
    size_ = 0;
}

void DoubleLinkedList::push_back(std::string data)
{
    ListNode *new_node = new ListNode{tail_, nullptr, nullptr, data};

    if (head_->next)
    {
        tail_->next = new_node;
    }
    else
    {
        head_->next = new_node;
    }

    tail_ = new_node;
    size_++;
}

size_t DoubleLinkedList::size() const noexcept
{
    return size_;
}

void DoubleLinkedList::swap(DoubleLinkedList &other) noexcept
{
    std::swap(head_->next, other.head_->next);
    std::swap(tail_, other.tail_);
    std::swap(size_, other.size_);
}
