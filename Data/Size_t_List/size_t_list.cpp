#include "size_t_list.hpp"
#include <stddef.h>

namespace experis {

/* Size_t_Node */

Size_t_Node::Size_t_Node(D_TYPE a_data, Size_t_Node *a_prev, Size_t_Node *a_next) noexcept
: m_data(a_data)   // Member Initialization Size_t_List - MIL
, m_prev(a_prev)
, m_next(a_next)
{
}

Size_t_Node::~Size_t_Node() noexcept{
}

D_TYPE Size_t_Node::Get() const noexcept {
    return this->m_data;
}

Size_t_Node* Size_t_Node::Prev() const noexcept {
    return this->m_prev;
}

Size_t_Node* Size_t_Node::Next() const noexcept {
    return this->m_next;
}

void Size_t_Node::SetPrev(Size_t_Node *a_prev) noexcept {
    this->m_prev = a_prev;
}

void Size_t_Node::SetNext(Size_t_Node *a_next) noexcept {
    this->m_next = a_next;
}

void Size_t_Node::Set(D_TYPE a_data, Size_t_Node *a_prev, Size_t_Node *a_next) noexcept {
    this->m_data = a_data;
    this->m_prev = a_prev;
    this->m_next = a_next;
}

/* Size_t_List */

Size_t_List::Size_t_List() noexcept
: m_head(DEFAULT_VAL, &this->m_head, &this->m_tail)
, m_tail(DEFAULT_VAL, &this->m_head, &this->m_tail)
{
}

Size_t_List::~Size_t_List() noexcept {
    this->Clear();
}

Size_t_List::Size_t_List(const Size_t_List& a_other) 
: m_head(DEFAULT_VAL, &this->m_head, &this->m_tail)
, m_tail(DEFAULT_VAL, &this->m_head, &this->m_tail)
{
    this->Copy(&a_other);
}

Size_t_List& Size_t_List::operator=(const Size_t_List& a_other) {
    this->Clear();

    this->m_head.Set(DEFAULT_VAL, &this->m_head, &this->m_tail);
    this->m_tail.Set(DEFAULT_VAL, &this->m_head, &this->m_tail);
    this->Copy(&a_other);
    return *this;
}

void Size_t_List::PushHead(D_TYPE a_value) {
    Size_t_Node *node = new Size_t_Node(a_value, &this->m_head, this->m_head.Next());
    this->m_head.SetNext(node);
    node->Next()->SetPrev(node);
}

void Size_t_List::PushTail(D_TYPE a_value) {
    Size_t_Node *node = new Size_t_Node(a_value, &this->m_head, this->m_head.Next());
    this->m_tail.Prev()->SetNext(node);
    this->m_tail.SetPrev(node);
}

size_t Size_t_List::Size() const noexcept {
	size_t counter = 0;
	Size_t_Node* read = this->m_head.Next();

	while(read != this->m_tail.Next()) {			
		read = read->Next();
		++counter;				
	}	
    return counter;     
}

const Size_t_Node *Size_t_List::Head() const noexcept {
    return &this->m_head;
}

const Size_t_Node *Size_t_List::Tail() const noexcept {
    return &this->m_tail;
}

void Size_t_List::Copy(const Size_t_List *a_other) {
    Size_t_Node *read = a_other->m_head.Next();
    while (read != a_other->m_tail.Next()) {
        this->PushHead(read->Get());
        read = read->Next();
    }
}

void Size_t_List::Clear() noexcept {
    Size_t_Node* read = this->m_head.Next();

	while(read != this->m_tail.Next()) {			
		read = read->Next();
        delete read->Prev();
    }
}

D_TYPE Size_t_List::Get(size_t a_indexOfValue) const noexcept {
	size_t counter = 0;
	Size_t_Node* read = this->m_head.Next();

	while(read != this->m_tail.Next()) {			
        if (counter == a_indexOfValue) {
            return read->Get();
        }
		read = read->Next();
		++counter;				
	}	
    return 0;     
}

size_t Size_t_List::ForEach(Act a_action, void* a_context) const {
    size_t i = 0;
    for (Size_t_Node *read = this->m_head.Next();
         read != this->m_tail.Next();
         read = read->Next(), ++i) {
            if (a_action(read->Get(), a_context) == false) {
                break;
            }
    }
    return i;
}

} // experis
