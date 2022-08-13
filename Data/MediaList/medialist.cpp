#include "medialist.hpp"
#include <stddef.h>

/* Node */

Node::Node(TYPE a_data, Node *a_prev, Node *a_next) noexcept
: m_data(a_data)   // Member Initialization List - MIL
, m_prev(a_prev)
, m_next(a_next)
{
}

Node::~Node() noexcept{
    if (DELETE) {
        delete this->m_data;
    }
}

TYPE Node::Get() const noexcept {
    return this->m_data;
}

Node* Node::Prev() const noexcept {
    return this->m_prev;
}

Node* Node::Next() const noexcept {
    return this->m_next;
}

void Node::SetPrev(Node *a_prev) noexcept {
    this->m_prev = a_prev;
}

void Node::SetNext(Node *a_next) noexcept {
    this->m_next = a_next;
}

void Node::Set(TYPE a_data, Node *a_prev, Node *a_next) noexcept {
    this->m_data = a_data;
    this->m_prev = a_prev;
    this->m_next = a_next;
}

/* MediaList */

MediaList::MediaList() noexcept
: m_head(DEFAULT_VALUE, &this->m_head, &this->m_tail)
, m_tail(DEFAULT_VALUE, &this->m_head, &this->m_tail)
{
}

MediaList::~MediaList() noexcept {
    this->Clear();
}

MediaList::MediaList(const MediaList& a_other) 
: m_head(DEFAULT_VALUE, &this->m_head, &this->m_tail)
, m_tail(DEFAULT_VALUE, &this->m_head, &this->m_tail)
{
    this->Copy(&a_other);
}

MediaList& MediaList::operator=(const MediaList& a_other) {
    this->Clear();

    this->m_head.Set(DEFAULT_VALUE, &this->m_head, &this->m_tail);
    this->m_tail.Set(DEFAULT_VALUE, &this->m_head, &this->m_tail);
    this->Copy(&a_other);
    return *this;
}

void MediaList::PushHead(TYPE a_value) {
    Node *node = new Node(a_value, &this->m_head, this->m_head.Next());
    this->m_head.SetNext(node);
    node->Next()->SetPrev(node);
}

void MediaList::PushTail(TYPE a_value) {
    Node *node = new Node(a_value, &this->m_head, this->m_head.Next());
    this->m_tail.Prev()->SetNext(node);
    this->m_tail.SetPrev(node);
}

size_t MediaList::Size() const noexcept {
	size_t counter = 0;
	Node* read = this->m_head.Next();

	while(read != this->m_tail.Next()) {			
		read = read->Next();
		++counter;				
	}	
    return counter;     
}

const Node *MediaList::Head() const noexcept {
    return &this->m_head;
}

const Node *MediaList::Tail() const noexcept {
    return &this->m_tail;
}

void MediaList::Copy(const MediaList *a_other) {
    Node *read = a_other->m_head.Next();
    while (read != a_other->m_tail.Next()) {
        this->PushHead(read->Get());
        read = read->Next();
    }
}

void MediaList::Clear() noexcept {
    Node* read = this->m_head.Next();

	while(read != this->m_tail.Next()) {			
		read = read->Next();
        delete read->Prev();
    }
}

TYPE MediaList::Get(size_t a_indexOfValue) const noexcept {
	size_t counter = 0;
	Node* read = this->m_head.Next();

	while(read != this->m_tail.Next()) {			
        if (counter == a_indexOfValue) {
            return read->Get();
        }
		read = read->Next();
		++counter;				
	}	
    return 0;     
}

size_t MediaList::ForEach(act a_action, void* a_context) {
    size_t i = 0;
    for (Node *read = this->m_head.Next();
         read != this->m_tail.Next();
         read = read->Next(), ++i) {
            if (a_action(read->Get(), a_context) == false) {
                break;
            }
    }
    return i;
}

size_t MediaList::ForEach(safeAct a_action, void* a_context) const {
    size_t i = 0;
    for (Node *read = this->m_head.Next();
         read != this->m_tail.Next();
         read = read->Next(), ++i) {
            if (a_action(read->Get(), a_context) == false) {
                break;
            }
    }
    return i;
}
