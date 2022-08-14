#ifndef HOMELIBRARY_UTILITIES_H
#define HOMELIBRARY_UTILITIES_H

#include "medialist.hpp"
#include "size_t_list.hpp"

/* ListAndIndex */

struct ListAndIndex {
public:
    ListAndIndex(const MediaList *a_mediaList);
    ListAndIndex(const MediaList *a_mediaList, size_t a_startFrom);

    size_t Get() const noexcept;
    const MediaList* GetList() const noexcept;

    void Advance() noexcept;
    void Print(size_t a_idx) const noexcept; 

private:
    size_t m_idx;
    const MediaList *m_mediaList;
};

/* SearchContext */

struct SearchContext {
public:
    SearchContext(bool a_searchForLoaned) noexcept;
    ~SearchContext() = default;

    Size_t_List* GetBooksIndexes() noexcept;
    Size_t_List* GetCDsIndexes() noexcept;
    const char* GetSearchKey() const noexcept;
    size_t GetIdx(const Media_t a_medioum) const noexcept;

    void Advance(const Media_t a_medioum) noexcept;

    const bool m_searchForLoaned;

private:
    Size_t_List m_booksIndexes;
    size_t m_booksIdx;
    Size_t_List m_cdsIndexes;
    size_t m_cdsIdx;
    char m_searchFor[MAX_NAME_LEN];
};

#endif /* HOMELIBRARY_UTILITIES_H */