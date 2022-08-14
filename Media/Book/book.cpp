#include "book.hpp"
#include <stdio.h> /* printf, FILE, fprintf */
#include <string.h> /* strlen */
#include <strings.h> /* strncasecmp */
#include "name.hpp"

Book::Book() noexcept
: m_book_name("Please Insert Book's Name: ", true)
, m_author("Please Insert Author's Name: ", true)
{
    printf("Book Added\n");
}

Book::Book(const char *a_bookName, const char *a_authorName) noexcept 
: m_book_name(a_bookName)
, m_author(a_authorName)
{
}

const Name& Book::GetName() const noexcept {
    return this->m_book_name;
}

const Name& Book::GetAuthor() const noexcept {
    return this->m_author;
}

void Book::FormatDetails(char *a_buffer, size_t a_length) const {
    snprintf(a_buffer, a_length, "Book Title: %s | Written By: %s", this->m_book_name.GetName(), this->m_author.GetName());
}

void Book::Save(FILE* a_fileStream) const {
    fprintf(a_fileStream, "%s\n%s\n", this->m_book_name.GetName(), this->m_author.GetName());
}
