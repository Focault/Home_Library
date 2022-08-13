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

const Name& Book::Get() const noexcept {
    return this->m_book_name;
}

void Book::Print(bool a_isLoaned) const noexcept {
    a_isLoaned ? printf("* ") : printf("  ");
    printf("Book Title: %s | Written By: %s\n", this->m_book_name.GetName(), this->m_author.GetName());
}

void Book::Details(bool a_isLoaned, const Name& a_loanedTo) const noexcept {
    this->Print(a_isLoaned);
    printf("  Loaned? - ");
    fputs(a_isLoaned ? "true" : "false", stdout);
    a_isLoaned ? printf("\tLoaned To %s\n\n", a_loanedTo.GetName()) : putchar('\n');
}

bool Book::IsNameBeginWith(const char *a_name_shred) const noexcept {
    size_t keyLen = strlen(a_name_shred);
    return (0 == strncasecmp(this->m_book_name.GetName(), a_name_shred, keyLen) || 
            0 == strncasecmp(this->m_author.GetName(), a_name_shred, keyLen));
}

void Book::Save(FILE* a_fileStream) const {
    fprintf(a_fileStream, "%s\n%s\n", this->m_book_name.GetName(), this->m_author.GetName());
}
