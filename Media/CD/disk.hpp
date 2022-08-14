#ifndef HOMELIBRARY_DISK_H
#define HOMELIBRARY_DISK_H

#include <stdio.h> /* FILE */
#include "name.hpp"

enum Disk_t {
    MUSIC,
    MOVIE
};

class Disk {
public:
    explicit Disk() noexcept;
    explicit Disk(const char *a_cd_name, bool a_isOriginal, Disk_t a_cdType, const char *a_artist) noexcept;

    ~Disk() = default;

    Disk& operator=(const Disk& a_cd) = default;

    const Name& GetName() const noexcept;
    const Name& GetArtist() const noexcept;

    // Minimum Size of Buffer should be 200 bytes
    void FormatDetails(char *a_buffer, size_t a_length) const;

    void Save(FILE* a_fileStream) const;

private:
    const Name m_cd_name;
    bool m_isOriginal;
    Disk_t m_cdType;
    Name m_artist;
};

#endif /* HOMELIBRARY_DISK_H */