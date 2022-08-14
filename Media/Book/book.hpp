#ifndef HOMELIBRARY_BOOK_H
#define HOMELIBRARY_BOOK_H

#include "name.hpp"
#include <stdio.h> /* FILE */

namespace experis {

class Book {
public:
    explicit Book() noexcept;
    explicit Book(const char *a_bookName, const char *a_authorName) noexcept; 
    ~Book() = default;

    Book& operator=(const Book& a_book) = default;

    const Name& GetName() const noexcept;
    const Name& GetAuthor() const noexcept;

    // Minimum Size of Buffer should be 200 bytes
    void FormatDetails(char *a_buffer, size_t a_length) const;

    void Save(FILE* a_fileStream) const;

private:
    const Name m_book_name;
    const Name m_author;
};

} // experis

#endif /* HOMELIBRARY_BOOK_H */