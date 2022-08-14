#ifndef HOMELIBRARY_LIST_H
#define HOMELIBRARY_LIST_H

#include <stddef.h> /* size_t */

namespace experis {

namespace details {

namespace list {

template<typename T>
class Node {
    public:
        typedef T Data;

        explicit Node(Data a_data, Node *a_prev, Node *a_next, bool a_deleteAtEnd) noexcept;
        explicit Node(Node *a_prev, Node *a_next, bool a_deleteAtEnd) noexcept;
        ~Node() noexcept;
        Node(const Node& a_other) = default;
        Node& operator=(const Node& a_other) = default;

        const Data& Get() const noexcept;
        Data& Get() noexcept;

        Node *Prev() const noexcept;
        Node *Next() const noexcept;

        void SetPrev(Node *a_prev) noexcept;
        void SetNext(Node *a_next) noexcept;

        void Set(Data a_data, Node *a_prev, Node *a_next) noexcept;
        void Set(Node *a_prev, Node *a_next) noexcept;
        void Set(Node *a_prev, Node *a_next, bool a_deleteAtEnd) noexcept;

    private:
        Data m_data;
        Node *m_prev;
        Node *m_next;
        bool m_deleteAtEnd;
    };

} // details
} // list

template<typename T>
class List {
public:
    typedef T Data;

    /* returns false for stopping the iteration */
    typedef bool (*act)(Data a_data, void* a_context);
    typedef bool (*safeAct)(const Data a_data, void* a_context);

    explicit List() noexcept;
    explicit List(bool a_deleteAtEnd) noexcept; // default is false
    List(const List& a_other);
    List& operator=(const List& a_other);
    ~List() noexcept;

    void PushHead(Data a_value);
    void PushTail(Data a_value);

    size_t Size() const noexcept;
    bool isEmpty() const noexcept;

    void Copy(const List *a_other);
    void Clear() noexcept;

    /* returns default value if out of bound */
    Data& Get(size_t a_indexOfValue) noexcept;
    const Data& Get(size_t a_indexOfValue) const noexcept;

    /* returns default value if empty */
    Data& GetHead();
    const Data& GetHead() const;
    Data& GetTail();
    const Data& GetTail() const;

    /* returns index of termination */
    size_t ForEach(act a_action, void* a_context);
    size_t ForEach(safeAct a_action, void* a_context) const;

private:
    class Node;

    details::list::Node<Data> m_head;
    details::list::Node<Data> m_tail;
    bool m_deleteAtEnd;
};

} // experis

#endif /* HOMELIBRARY_LIST_H */