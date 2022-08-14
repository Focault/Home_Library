#ifndef HOMELIBRARY_MEDIA_H
#define HOMELIBRARY_MEDIA_H

#include <stdio.h> /* FILE */
#include "book.hpp"
#include "name.hpp"
#include "disk.hpp"

namespace experis {

enum Media_t {
    CD,
    BOOK
};

// Manage Loanable Media
class Media {
public:
    explicit Media(Media_t a_medioum);
    explicit Media(FILE* a_fileStream, Media_t a_medioum);
    ~Media() noexcept;
    
    Media& operator=(const Media& a_media);

    const Media_t Medioum() const noexcept;

    void Print() const noexcept;
    void Details() const noexcept;
    
    void MarkLoaned();
    void MarkReturned();

    bool IsNameBeginWith(const char *a_name_shred) const noexcept;

    bool IsLoaned() const noexcept;

    void Save(FILE* a_fileStream) const;

private:
    Book *m_book;
    Disk *m_cd;
    Media_t m_medioum;
    bool m_isLoaned;
    Name m_loanedTo;
};

/**
 * @brief Load a new media unit from file
 * 
 * @param a_fileStream 
 * @param a_newMedia - to load new allocated media into
 * @param a_medioum - to load new media's unit medioum into
 * @return true - unit loaded
 * @return false - reached EOF
 */
bool LoadMediaUnit(FILE* a_fileStream, Media **a_newMedia, Media_t *a_medioum);

} // experis

#endif /* HOMELIBRARY_MEDIA_H */