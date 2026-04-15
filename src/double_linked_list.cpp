#include "double_linked_list.h"

DoubleLinkedList::DoubleLinkedList():head_(new ListNode){
}

DoubleLinkedList::~DoubleLinkedList(){
    Clear();
}

DoubleLinkedList::DoubleLinkedList(DoubleLinkedList&& other):
    head_(std::move(other.head_)){}

DoubleLinkedList& DoubleLinkedList::operator=(DoubleLinkedList&& other) noexcept{
    DoubleLinkedList tpm(std::move(other));
    this->swap(tpm);
    return *this;
}

void DoubleLinkedList::Clear() noexcept{
    while(head_->next){
        auto node = head_->next;
        head_->next = head_->next->next;
        delete node;
    }

    delete head_;
}

// void DoubleLinkedList::PushBack(std::string data, int rand_index){

// }

void DoubleLinkedList::swap(DoubleLinkedList& other) noexcept {
    std::swap( head_->next, other.head_->next);
}

