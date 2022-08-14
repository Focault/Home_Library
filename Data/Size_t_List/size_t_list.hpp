#ifndef HOMELIBRARY_SIZE_T_LIST_H
#define HOMELIBRARY_SIZE_T_LIST_H

#include <stddef.h>

#define D_TYPE size_t
#define DEFAULT_VAL 0

/* returns false for stopping the iteration */
typedef bool (*Act)(D_TYPE a_data, void* a_context);

class Size_t_Node {
public:
    explicit Size_t_Node(D_TYPE a_data, Size_t_Node *a_prev, Size_t_Node *a_next) noexcept;
    ~Size_t_Node() noexcept;

    D_TYPE Get() const noexcept;

    Size_t_Node *Prev() const noexcept;
    Size_t_Node *Next() const noexcept;

    void SetPrev(Size_t_Node *a_prev) noexcept;
    void SetNext(Size_t_Node *a_next) noexcept;

    void Set(D_TYPE a_data, Size_t_Node *a_prev, Size_t_Node *a_next) noexcept;

private:
    D_TYPE m_data;
    Size_t_Node *m_prev;
    Size_t_Node *m_next;
};

class Size_t_List {
public:
    explicit Size_t_List() noexcept;
    ~Size_t_List() noexcept;
    Size_t_List(const Size_t_List& a_other);
    Size_t_List& operator=(const Size_t_List& a_other);

    void PushHead(D_TYPE a_value);
    void PushTail(D_TYPE a_value);

    size_t Size() const noexcept;

    const Size_t_Node *Head() const noexcept;
    const Size_t_Node *Tail() const noexcept;

    void Copy(const Size_t_List *a_other);
    void Clear() noexcept;

    /* returns 0 if out of bound */
    D_TYPE Get(size_t a_indexOfValue) const noexcept;

    /* returns index of termination */
    size_t ForEach(Act a_action, void* a_context) const;

private:
    Size_t_Node m_head;
    Size_t_Node m_tail;
};

#endif /* HOMELIBRARY_SIZE_T_LIST_H */