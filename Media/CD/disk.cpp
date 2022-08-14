#include "disk.hpp"
#include <stdio.h> /* printf, FILE, fprintf */
#include <string.h> /* strlen */
#include "name.hpp"
#include "ui.hpp"

namespace experis {

Disk::Disk() noexcept 
: m_cd_name("Please Enter CD Name: ", true)
, m_isOriginal(AskYorN("Is The CD Original?"))
, m_cdType(Disk_t(Ask("What Is The CD Type?", "Music", "Movie")))
, m_artist(" ", false)
{
    if (this->m_cdType == MUSIC) {
        Name artist{"Please Enter CD's Singer\\Band\\Creator: ", true};
        m_artist = artist;
    }
}

Disk::Disk(const char *a_cd_name, bool a_isOriginal, Disk_t a_cdType, const char *a_artist) noexcept 
: m_cd_name(a_cd_name)
, m_isOriginal(a_isOriginal)
, m_cdType(a_cdType)
, m_artist(a_artist)
{
}

const Name& Disk::GetName() const noexcept {
    return this->m_cd_name;
}

const Name& Disk::GetArtist() const noexcept {
    return this->m_artist;
}

void Disk::FormatDetails(char *a_buffer, size_t a_length) const {
    const char *isOriginalStr = this->m_isOriginal ? "true" : "false";
    size_t offset = snprintf(a_buffer, a_length, "CD Title: %s | Is Original? %s | Type: ",
                                                 this->m_cd_name.GetName(), 
                                                 isOriginalStr);
    if (a_length > offset) {
        if (this->m_cdType == MUSIC) {
            snprintf(a_buffer + offset, a_length - offset, "Music | Artist: %s", this->m_artist.GetName());
        } 
        else {
            snprintf(a_buffer + offset, a_length - offset, "Movie");
        }
    }
}

void Disk::Save(FILE* a_fileStream) const {
    fprintf(a_fileStream, "%s\n%d\n%d\n%s\n", this->m_cd_name.GetName(), 
                                              (int)this->m_isOriginal, 
                                              (int)this->m_cdType, 
                                              this->m_artist.GetName());
}

} // experis
