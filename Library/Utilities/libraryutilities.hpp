#ifndef HOMELIBRARY_UTILITIES_H
#define HOMELIBRARY_UTILITIES_H

#include "list.hpp"
#include "media.hpp"

namespace experis {

/* ListAndIndex */

struct ListAndIndex {
public:
    ListAndIndex(const List<Media*> *a_mediaList);
    ListAndIndex(const List<Media*> *a_mediaList, size_t a_startFrom);

    size_t Get() const noexcept;
    const List<Media*>* GetList() const noexcept;

    void Advance() noexcept;
    void Print(size_t a_idx) const noexcept; 

private:
    size_t m_idx;
    const List<Media*> *m_mediaList;
};

/* SearchContext */

struct SearchContext {
public:
    SearchContext(bool a_searchForLoaned) noexcept;
    ~SearchContext() = default;

    List<size_t>& GetBooksIndexes() noexcept;
    List<size_t>& GetCDsIndexes() noexcept;
    const char* GetSearchKey() const noexcept;
    size_t GetIdx(const Media_t a_medioum) const noexcept;

    void Advance(const Media_t a_medioum) noexcept;

    const bool m_searchForLoaned;

private:
    List<size_t> m_booksIndexes;
    size_t m_booksIdx;
    List<size_t> m_cdsIndexes;
    size_t m_cdsIdx;
    char m_searchFor[MAX_NAME_LEN];
};

} // experis

#endif /* HOMELIBRARY_UTILITIES_H */