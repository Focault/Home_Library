#ifndef HOMELIBRARY_LIBRARY_H
#define HOMELIBRARY_LIBRARY_H

#include "media.hpp"
#include "ui.hpp"
#include "medialist.hpp"

namespace experis {

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

} // experis

#endif /* HOMELIBRARY_LIBRARY_H */