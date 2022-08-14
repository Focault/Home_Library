#ifndef HOMELIBRARY_LIBRARY_H
#define HOMELIBRARY_LIBRARY_H

#include "medialist.hpp"
#include "ui.hpp"

class Library {
public:
    explicit Library();
    ~Library() = default;

    void RunLibrary();

private:
    void ListAllMedia() const noexcept;
    void PrintDetails() const noexcept;
    void MarkLoaned();
    void MarkReturned();

    Media* Choose(bool a_searchForLoaned);

    void Save() const;
    void Load();

    MediaList m_books;
    MediaList m_cds;
    const UI m_interface;
};

#endif /* HOMELIBRARY_LIBRARY_H */