#include "double_linked_list.h"

DoubleLinkedList::DoubleLinkedList():head_(new ListNode){
}

DoubleLinkedList::~DoubleLinkedList(){
    Clear();
}

void DoubleLinkedList::Clear() noexcept{
    while(head_->next){
        auto node = head_->next;
        head_->next = head_->next->next;
        delete node;
    }

    delete head_;
}