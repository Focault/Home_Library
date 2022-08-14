#include "list.hpp"
#include <stddef.h>
#include "media.hpp"


namespace experis {

namespace details {

namespace list {

/* Node */

template<typename T>
Node<T>::Node(T a_data, Node<T> *a_prev, Node<T> *a_next, bool a_deleteAtEnd) noexcept
: m_data(a_data)
, m_prev(a_prev)
, m_next(a_next)
, m_deleteAtEnd(a_deleteAtEnd)
{
}

template<typename T>
Node<T>::Node(Node<T> *a_prev, Node<T> *a_next, bool a_deleteAtEnd) noexcept
: m_data()
, m_prev(a_prev)
, m_next(a_next)
, m_deleteAtEnd(a_deleteAtEnd)
{
}

template<typename T>
Node<T>::~Node() noexcept {
    if (this->m_deleteAtEnd == true) {
        delete this->m_data;
    }
}

template<>
Node<size_t>::~Node() noexcept {
    // do nothing
}

template<>
Node<long>::~Node() noexcept {
    // do nothing
}

template<>
Node<char>::~Node() noexcept {
    // do nothing
}

template<>
Node<unsigned char>::~Node() noexcept {
    // do nothing
}

template<>
Node<int>::~Node() noexcept {
    // do nothing
}

template<>
Node<unsigned int>::~Node() noexcept {
    // do nothing
}

template<>
Node<bool>::~Node() noexcept {
    // do nothing
}

template<>
Node<short>::~Node() noexcept {
    // do nothing
}

template<>
Node<unsigned short>::~Node() noexcept {
    // do nothing
}

template<typename T>
const typename Node<T>::Data& Node<T>::Get() const noexcept {
    return this->m_data;
}

template<typename T>
typename Node<T>::Data& Node<T>::Get() noexcept {
    return this->m_data;
}

template<typename T>
Node<T>* Node<T>::Prev() const noexcept {
    return this->m_prev;
}

template<typename T>
Node<T>* Node<T>::Next() const noexcept {
    return this->m_next;
}

template<typename T>
void Node<T>::SetPrev(Node<T> *a_prev) noexcept {
    this->m_prev = a_prev;
}

template<typename T>
void Node<T>::SetNext(Node<T> *a_next) noexcept {
    this->m_next = a_next;
}

template<typename T>
void Node<T>::Set(T a_data, Node<T> *a_prev, Node<T> *a_next) noexcept {
    this->m_data = a_data;
    this->m_prev = a_prev;
    this->m_next = a_next;
}

template<typename T>
void Node<T>::Set(Node<T> *a_prev, Node<T> *a_next) noexcept {
    this->m_prev = a_prev;
    this->m_next = a_next;
}

template<typename T>
void Node<T>::Set(Node<T> *a_prev, Node<T> *a_next, bool a_deleteAtEnd) noexcept {
    this->m_prev = a_prev;
    this->m_next = a_next;
    this->m_deleteAtEnd = a_deleteAtEnd;
}

} // details
} // list

/* List */

template<typename T>
List<T>::List() noexcept
: m_head(&this->m_head, &this->m_tail, false)
, m_tail(&this->m_head, &this->m_tail, false)
, m_deleteAtEnd(false)
{
}

template<typename T>
List<T>::List(bool a_deleteAtEnd) noexcept 
: m_head(&this->m_head, &this->m_tail, a_deleteAtEnd)
, m_tail(&this->m_head, &this->m_tail, a_deleteAtEnd)
, m_deleteAtEnd(a_deleteAtEnd)
{
}

template<typename T>
List<T>::~List() noexcept {
    this->Clear();
}

template<typename T>
List<T>::List(const List& a_other) 
: m_head(&this->m_head, &this->m_tail, a_other.m_deleteAtEnd)
, m_tail(&this->m_head, &this->m_tail, a_other.m_deleteAtEnd)
, m_deleteAtEnd(a_other.m_deleteAtEnd)
{
    this->Copy(&a_other);
}

template<typename T>
List<T>& List<T>::operator=(const List& a_other) {
    this->Clear();
    this->m_deleteAtEnd = a_other.m_deleteAtEnd;
    this->m_head.Set(&this->m_head, &this->m_tail, this->m_deleteAtEnd);
    this->m_tail.Set(&this->m_head, &this->m_tail, this->m_deleteAtEnd);
    this->Copy(&a_other);
    return *this;
}

template<typename T>
void List<T>::PushHead(T a_value) {
    details::list::Node<T> *node = new details::list::Node<T>(a_value, &this->m_head, this->m_head.Next(), this->m_deleteAtEnd);
    this->m_head.SetNext(node);
    node->Next()->SetPrev(node);
}

template<typename T>
void List<T>::PushTail(T a_value) {
    details::list::Node<T> *node = new details::list::Node<T>(a_value, this->m_tail.Prev(), &this->m_tail, this->m_deleteAtEnd);
    this->m_tail.Prev()->SetNext(node);
    this->m_tail.SetPrev(node);
}

template<typename T>
size_t List<T>::Size() const noexcept {
	size_t counter = 0;
	details::list::Node<T>* read = this->m_head.Next();

	while(read != this->m_tail.Next()) {			
		read = read->Next();
		++counter;				
	}	
    return counter;     
}

template<typename T>
bool List<T>::isEmpty() const noexcept {
    return (this->m_head.Next() == this->m_tail.Next());     
}

template<typename T>
void List<T>::Copy(const List *a_other) {
    details::list::Node<T> *read = a_other->m_head.Next();
    while (read != a_other->m_tail.Next()) {
        this->PushHead(read->Get());
        read = read->Next();
    }
}

template<typename T>
void List<T>::Clear() noexcept {
    details::list::Node<T>* read = this->m_head.Next();

	while(read != this->m_tail.Next()) {			
		read = read->Next();
        delete read->Prev();
    }
}

template<typename T>
const typename List<T>::Data& List<T>::Get(size_t a_indexOfValue) const noexcept {
	size_t counter = 0;
	details::list::Node<T>* read = this->m_head.Next();

	while(read != this->m_tail.Next()) {			
        if (counter == a_indexOfValue) {
            return read->Get();
        }
		read = read->Next();
		++counter;				
	}	
    return this->m_head.Get();     
}

template<typename T>
typename List<T>::Data& List<T>::Get(size_t a_indexOfValue) noexcept {
	size_t counter = 0;
	details::list::Node<T>* read = this->m_head.Next();

	while(read != this->m_tail.Next()) {			
        if (counter == a_indexOfValue) {
            return read->Get();
        }
		read = read->Next();
		++counter;				
	}	
    return this->m_head.Get();     
}

template<typename T>
typename List<T>::Data& List<T>::GetHead() {
    return this->m_head.Next()->Get();     
}

template<typename T>
const typename List<T>::Data& List<T>::GetHead() const {
    return this->m_head.Next()->Get();     
}

template<typename T>
typename List<T>::Data& List<T>::GetTail() {
    return this->m_tail.Prev()->Get();     
}

template<typename T>
const typename List<T>::Data& List<T>::GetTail() const {
    return this->m_tail.Prev()->Get();     
}

template<typename T>
size_t List<T>::ForEach(act a_action, void* a_context) {
    size_t i = 0;
    for (details::list::Node<T> *read = this->m_head.Next();
         read != this->m_tail.Next();
         read = read->Next(), ++i) {
            if (a_action(read->Get(), a_context) == false) {
                break;
            }
    }
    return i;
}

template<typename T>
size_t List<T>::ForEach(safeAct a_action, void* a_context) const {
    size_t i = 0;
    for (details::list::Node<T> *read = this->m_head.Next();
         read != this->m_tail.Next();
         read = read->Next(), ++i) {
            if (a_action(read->Get(), a_context) == false) {
                break;
            }
    }
    return i;
}

template class List<size_t>;
template class List<Media*>;

} // experis
