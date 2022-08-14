#ifndef HOMELIBRARY_MEDIALIST_H
#define HOMELIBRARY_MEDIALIST_H

#include <stddef.h>
#include "media.hpp"

#define TYPE Media*
#define DEFAULT_VALUE nullptr
#define DELETE true

/* returns false for stopping the iteration */
typedef bool (*act)(TYPE a_data, void* a_context);
/* returns false for stopping the iteration */
typedef bool (*safeAct)(const TYPE a_data, void* a_context);

class Node {
public:
    explicit Node(TYPE a_data, Node *a_prev, Node *a_next) noexcept;
    ~Node() noexcept;

    TYPE Get() const noexcept;

    Node *Prev() const noexcept;
    Node *Next() const noexcept;

    void SetPrev(Node *a_prev) noexcept;
    void SetNext(Node *a_next) noexcept;

    void Set(TYPE a_data, Node *a_prev, Node *a_next) noexcept;

private:
    TYPE m_data;
    Node *m_prev;
    Node *m_next;
};

class MediaList {
public:
    explicit MediaList() noexcept;
    ~MediaList() noexcept;
    MediaList(const MediaList& a_other);
    MediaList& operator=(const MediaList& a_other);

    void PushHead(TYPE a_value);
    void PushTail(TYPE a_value);

    size_t Size() const noexcept;

    const Node *Head() const noexcept;
    const Node *Tail() const noexcept;

    void Copy(const MediaList *a_other);
    void Clear() noexcept;

    /* returns 0 if out of bound */
    TYPE Get(size_t a_indexOfValue) const noexcept;

    /* returns index of termination */
    size_t ForEach(act a_action, void* a_context);
    size_t ForEach(safeAct a_action, void* a_context) const;

private:
    Node m_head;
    Node m_tail;
};

#endif /* HOMELIBRARY_MEDIALIST_H */