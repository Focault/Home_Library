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

    const Name& Get() const noexcept;

    void Print(bool a_isLoaned) const noexcept;
    void Details(bool a_isLoaned, const Name& a_loanedTo) const noexcept;

    bool IsNameBeginWith(const char *a_name_shred) const noexcept;

    void Save(FILE* a_fileStream) const;

private:
    const Name m_cd_name;
    bool m_isOriginal;
    Disk_t m_cdType;
    Name m_artist;
};

#endif /* HOMELIBRARY_DISK_H */