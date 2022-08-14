#include "media.hpp"
#include "list.hpp"
#include "libraryutilities.hpp"
#include "ui.hpp"

namespace experis {

/* ListAndIndex */

ListAndIndex::ListAndIndex(const List<Media*> *a_mediaList) 
: m_idx(0)
, m_mediaList(a_mediaList)
{
}

ListAndIndex::ListAndIndex(const List<Media*> *a_mediaList, size_t a_startFrom) 
: m_idx(a_startFrom)
, m_mediaList(a_mediaList)
{
}

size_t ListAndIndex::Get() const noexcept {
    return this->m_idx;
}

const List<Media*>* ListAndIndex::GetList() const noexcept {
    return this->m_mediaList;
}

void ListAndIndex::Advance() noexcept {
    this->m_idx += 1;
}

void ListAndIndex::Print(size_t a_idx) const noexcept {
    printf("(%lu)", this->m_idx);
    this->m_mediaList->Get(a_idx)->Print();
}

/* SearchContext */

SearchContext::SearchContext(bool a_searchForLoaned) noexcept
: m_booksIndexes()
, m_booksIdx(0)
, m_cdsIndexes()
, m_cdsIdx(0)
, m_searchFor()
, m_searchForLoaned(a_searchForLoaned)
{
    AskInput("Please Insert Search Key: ", this->m_searchFor, MAX_NAME_LEN);
}

List<size_t>& SearchContext::GetBooksIndexes() noexcept {
    return this->m_booksIndexes;
}

List<size_t>& SearchContext::GetCDsIndexes() noexcept {
    return this->m_cdsIndexes;
}

const char* SearchContext::GetSearchKey() const noexcept {
    return this->m_searchFor;
}

size_t SearchContext::GetIdx(const Media_t a_medioum) const noexcept {
    switch (a_medioum) {
    case BOOK:
        return this->m_booksIdx;
    case CD:
        return this->m_cdsIdx;
    }
    return 0;
}

void SearchContext::Advance(const Media_t a_medioum) noexcept {
    switch (a_medioum) {
    case BOOK:
        this->m_booksIdx += 1;
        break;
    case CD:
        this->m_cdsIdx += 1;
        break;
    }
}

} // experis
