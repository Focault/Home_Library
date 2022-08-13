#include "disk.hpp"
#include <stdio.h> /* printf, FILE, fprintf */
#include <string.h> /* strlen */
#include <strings.h> /* strncasecmp */
#include "name.hpp"
#include "ui.hpp"

Disk::Disk() noexcept 
: m_cd_name("Please Enter CD Name: ", true)
, m_isOriginal(AskYorN("Is The CD Original?"))
, m_cdType(Disk_t(Ask("What Is The CD Type?", "Music", "Movie")))
, m_artist(" ", false)
{
    if (this->m_cdType == MUSIC) {
        Name artist{"Please Enter CD's Singer\\Band: ", true};
        m_artist = artist;
    }
}

Disk::Disk(const Name a_cd_name, bool a_isOriginal, Disk_t a_cdType, Name a_artist) noexcept 
: m_cd_name(a_cd_name)
, m_isOriginal(a_isOriginal)
, m_cdType(a_cdType)
, m_artist(a_artist)
{
}

const Name& Disk::Get() const noexcept {
    return this->m_cd_name;
}

void Disk::Print(bool a_isLoaned) const noexcept {
    a_isLoaned ? printf("* ") : printf("  ");
    printf("CD Title: %s | Is Original? ", this->m_cd_name.GetName());
    fputs(this->m_isOriginal ? "true" : "false", stdout);
    printf(" | Type: ");
    if (this->m_cdType == MUSIC) {
        printf("Music | Artist: %s\n", this->m_artist.GetName());
    } else {
        fputs("Movie\n", stdout);
    }
}

void Disk::Details(bool a_isLoaned, const Name& a_loanedTo) const noexcept {
    this->Print(a_isLoaned);
    printf("  Loaned? - ");
    fputs(a_isLoaned ? "true" : "false", stdout);
    a_isLoaned ? printf("\tLoaned To %s\n\n", a_loanedTo.GetName()) : putchar('\n');
}

bool Disk::IsNameBeginWith(const char *a_name_shred) const noexcept {
    size_t keyLen = strlen(a_name_shred);
    return (0 == strncasecmp(this->m_cd_name.GetName(), a_name_shred, keyLen) || 
            0 == strncasecmp(this->m_artist.GetName(), a_name_shred, keyLen));
}

void Disk::Save(FILE* a_fileStream) const {
    fprintf(a_fileStream, "%s\n%d\n%d\n%s\n", this->m_cd_name.GetName(), 
                                              (int)this->m_isOriginal, 
                                              (int)this->m_cdType, 
                                              this->m_artist.GetName());
}