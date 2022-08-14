#include "media.hpp"
#include <string.h> /* strlen */
#include <strings.h> /* strncasecmp */
#include <stdlib.h> /* atoi */
#include "book.hpp"
#include "name.hpp"
#include "disk.hpp"
#include "ui.hpp"

#define BOOL_FILE_SIZE sizeof("0\0\n")
#define BUFFER_SIZE 200


static char* RemoveNewLine(char *a_endWthNewLine);


/* Media */

Media::Media(Media_t a_medioum) 
: m_book(nullptr)
, m_cd(nullptr)
, m_medioum(a_medioum)
, m_isLoaned(false)
, m_loanedTo(" ", false)
{
    switch (a_medioum) {
    case BOOK:
        this->m_book = new Book();
        break;
    case CD:
        this->m_cd = new Disk();
        break;
    }
}

Media::Media(FILE* a_fileStream, Media_t a_medioum)
: m_book(nullptr)
, m_cd(nullptr)
, m_medioum(a_medioum)
, m_isLoaned(false)
, m_loanedTo(" ", false)
{
    char nameBufferOne[MAX_NAME_LEN], nameBufferTwo[MAX_NAME_LEN];
    char isOriginal[sizeof("0")], cdType[sizeof("0")];
    switch (a_medioum) {
    case BOOK:
        RemoveNewLine(fgets(nameBufferOne, MAX_NAME_LEN, a_fileStream));
        RemoveNewLine(fgets(nameBufferTwo, MAX_NAME_LEN, a_fileStream));
        this->m_book = new Book{nameBufferOne, nameBufferTwo};
        break;
    case CD:
        RemoveNewLine(fgets(nameBufferOne, MAX_NAME_LEN, a_fileStream));
        RemoveNewLine(fgets(isOriginal, BOOL_FILE_SIZE, a_fileStream));
        RemoveNewLine(fgets(cdType, sizeof("0\0\n"), a_fileStream));
        RemoveNewLine(fgets(nameBufferTwo, MAX_NAME_LEN, a_fileStream));
        this->m_cd = new Disk{nameBufferOne, (bool)atoi(isOriginal), (Disk_t)atoi(cdType), nameBufferTwo};
        break;
    }
    char isLoanedBuff[BOOL_FILE_SIZE], loanedToBuff[MAX_NAME_LEN];
    this->m_isLoaned = (bool)atoi(RemoveNewLine(fgets(isLoanedBuff, BOOL_FILE_SIZE, a_fileStream)));
    Name loaner{RemoveNewLine(fgets(loanedToBuff, MAX_NAME_LEN, a_fileStream))};
    this->m_loanedTo = loaner;
}

Media::~Media() noexcept {
    switch (this->m_medioum) {
    case BOOK:
        delete this->m_book;
        break;
    case CD:
        delete this->m_cd;
        break;
    }
}

Media& Media::operator=(const Media& a_media) {
    this->m_book = a_media.m_book;
    this->m_cd = a_media.m_cd;
    this->m_medioum = a_media.m_medioum;
    return *this;
}

const Media_t Media::Medioum() const noexcept {
    return this->m_medioum;
}

void Media::Print() const noexcept {
    char buffer[BUFFER_SIZE];
    switch (this->m_medioum) {
    case BOOK:
        this->m_book->FormatDetails(buffer, BUFFER_SIZE);
        PrintMedia(this->m_isLoaned, buffer);
        break;
    case CD:
        this->m_cd->FormatDetails(buffer, BUFFER_SIZE);
        PrintMedia(this->m_isLoaned, buffer);
        break;
    }
}

void Media::Details() const noexcept {
    char buffer[BUFFER_SIZE];
    switch (this->m_medioum) {
    case BOOK:
        this->m_book->FormatDetails(buffer, BUFFER_SIZE);
        PrintMediaDetails(this->m_isLoaned, buffer, this->m_loanedTo.GetName());
        break;
    case CD:
        this->m_cd->FormatDetails(buffer, BUFFER_SIZE);
        PrintMediaDetails(this->m_isLoaned, buffer, this->m_loanedTo.GetName());
        break;
    }
}

void Media::MarkLoaned() {
    this->m_isLoaned = true;
    Name loaner{"Please Insert Loaner's Name: ", true};
    m_loanedTo = loaner;
}

void Media::MarkReturned() {
    this->m_isLoaned = false;
    Name loaner{" ", false};
    m_loanedTo = loaner;
}

bool Media::IsNameBeginWith(const char *a_name_shred) const noexcept {
    size_t keyLen = strlen(a_name_shred);
    switch (this->m_medioum) {
    case BOOK:
        return (0 == strncasecmp(this->m_book->GetName().GetName(), a_name_shred, keyLen) || 
                0 == strncasecmp(this->m_book->GetAuthor().GetName(), a_name_shred, keyLen));
        break;
    case CD:
        return (0 == strncasecmp(this->m_cd->GetName().GetName(), a_name_shred, keyLen) || 
                0 == strncasecmp(this->m_cd->GetArtist().GetName(), a_name_shred, keyLen));
        break;
    }
    return false;
}

bool Media::IsLoaned() const noexcept {
    return m_isLoaned;
}

void Media::Save(FILE* a_fileStream) const {
    switch (this->m_medioum) {
    case BOOK:
        fprintf(a_fileStream, "B\n");
        this->m_book->Save(a_fileStream);
        break;
    case CD:
        fprintf(a_fileStream, "C\n");
        this->m_cd->Save(a_fileStream);
        break;
    }
    fprintf(a_fileStream, "%d\n%s\n", (int)this->m_isLoaned, this->m_loanedTo.GetName());
}

/* Functions */

bool LoadMediaUnit(FILE* a_fileStream, Media **a_newMedia, Media_t *a_medioum) {
    const int medioumSym = fgetc(a_fileStream);
    fseek(a_fileStream, 1, SEEK_CUR);
    if (feof(a_fileStream)) {
        return false;
    }
    switch ((char)medioumSym) {
    case 'B':
        *a_medioum = BOOK;
        break;
    case 'C':
        *a_medioum = CD;
        break;
    default:
        return false;
    }
    *a_newMedia = new Media{a_fileStream, *a_medioum};
    return true;
}

/* Static Functions */

static char* RemoveNewLine(char *a_endWthNewLine) {
    a_endWthNewLine[strlen(a_endWthNewLine) - 1] = '\0';
    return a_endWthNewLine;
}