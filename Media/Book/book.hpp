#ifndef HOMELIBRARY_BOOK_H
#define HOMELIBRARY_BOOK_H

#include "name.hpp"
#include <stdio.h> /* FILE */

class Book {
public:
    Book() noexcept;
    Book(const char *a_bookName, const char *a_authorName) noexcept; 
    ~Book() = default;

    Book& operator=(const Book& a_book) = default;

    const Name& Get() const noexcept;

    void Print(bool a_isLoaned) const noexcept;
    void Details(bool a_isLoaned, const Name& a_loanedTo) const noexcept;

    bool IsNameBeginWith(const char *a_name_shred) const noexcept;

    void Save(FILE* a_fileStream) const;

private:
    const Name m_book_name;
    const Name m_author;
};

#endif /* HOMELIBRARY_BOOK_H */