#include "library.hpp"
#include <stdio.h>
#include "medialist.hpp"
#include "size_t_list.hpp"
#include "media.hpp"
#include "ui.hpp"

#define FILE_NAME "Data/Memory.DATA"

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

ListAndIndex::ListAndIndex(const MediaList *a_mediaList) 
: m_idx(0)
, m_mediaList(a_mediaList)
{
}

ListAndIndex::ListAndIndex(const MediaList *a_mediaList, size_t a_startFrom) 
: m_idx(a_startFrom)
, m_mediaList(a_mediaList)
{
}

size_t ListAndIndex::Get() const noexcept {
    return this->m_idx;
}

const MediaList* ListAndIndex::GetList() const noexcept {
    return this->m_mediaList;
}

void ListAndIndex::Advance() noexcept {
    this->m_idx += 1;
}

void ListAndIndex::Print(size_t a_idx) const noexcept {
    printf("(%lu)", this->m_idx);
    this->m_mediaList->Get(a_idx)->Print();
}

struct Context {
public:
    Context(const char *a_searchFor, bool a_searchForLoaned) noexcept;
    ~Context() noexcept;

    Size_t_List* GetBooksIndexes() noexcept;
    Size_t_List* GetCDsIndexes() noexcept;
    const char* GetSearchKey() const noexcept;
    const bool GetSearchForLoanedStatus() const noexcept;
    size_t GetIdx(const Media_t a_medioum) const noexcept;

    void Advance(const Media_t a_medioum) noexcept;

private:
    Size_t_List m_booksIndexes;
    size_t m_booksIdx;
    Size_t_List m_cdsIndexes;
    size_t m_cdsIdx;
    const char *m_searchFor;
    const bool m_searchForLoaned;
};

Context::Context(const char *a_searchFor, bool a_searchForLoaned) noexcept
: m_booksIndexes()
, m_booksIdx(0)
, m_cdsIndexes()
, m_cdsIdx(0)
, m_searchFor(a_searchFor)
, m_searchForLoaned(a_searchForLoaned)
{
}

Context::~Context() noexcept {
    delete[] this->m_searchFor;
}

Size_t_List* Context::GetBooksIndexes() noexcept {
    return &this->m_booksIndexes;
}

Size_t_List* Context::GetCDsIndexes() noexcept {
    return &this->m_cdsIndexes;
}

const char* Context::GetSearchKey() const noexcept {
    return this->m_searchFor;
}

const bool Context::GetSearchForLoanedStatus() const noexcept {
    return this->m_searchForLoaned;
}

size_t Context::GetIdx(const Media_t a_medioum) const noexcept {
    switch (a_medioum) {
    case BOOK:
        return this->m_booksIdx;
    case CD:
        return this->m_cdsIdx;
    }
    return 0;
}

void Context::Advance(const Media_t a_medioum) noexcept {
    switch (a_medioum) {
    case BOOK:
        this->m_booksIdx += 1;
        break;
    case CD:
        this->m_cdsIdx += 1;
        break;
    }
}

static bool PrintAllAction(const Media* a_media, void* a_context);
static bool PrintDetailsForMatches(const Media* a_media, void* a_searchFor);
static bool SaveAllToFile(const Media* a_media, void* a_fileStream);
static bool ReturnIndexesOfMatches(const Media* a_media, void* a_context);
static bool PrintNumberedOption(size_t a_idx, void* a_listAndIndex);

Library::Library() 
: m_books()
, m_cds()
, m_interface()
{
    this->Load();
}

void Library::RunLibrary() {
    Option choose;
    while ((choose = this->m_interface.Menu()) != EXIT) {
        switch (choose) {
        case LIST:
            this->ListAllMedia();
            break;
        case PRINT_DETAILS:
            this->PrintDetails();
            break;
        case ADD_BOOK:
            this->m_books.PushHead(new Media(BOOK));
            break;
        case ADD_CD:
            this->m_cds.PushHead(new Media(CD));
            break;
        case MARK_LOANED:
            this->MarkLoaned();
            break;
        case MARK_RETURNED:
            this->MarkReturned();
            break;
        }
    }
    this->Save();
}

void Library::ListAllMedia() const noexcept {
    this->m_books.ForEach(PrintAllAction, nullptr);
    this->m_cds.ForEach(PrintAllAction, nullptr);
}

void Library::PrintDetails() const noexcept {
    const char *searchKey = this->m_interface.SearchFor();
    this->m_books.ForEach(PrintDetailsForMatches, (void*)searchKey);
    this->m_cds.ForEach(PrintDetailsForMatches, (void*)searchKey);
    delete[] searchKey;
}

void Library::MarkLoaned() {
    Media *loaned = this->Choose(false);
    if (loaned != nullptr) {
        loaned->MarkLoaned();
    }
}

void Library::MarkReturned() {
    Media *loaned = this->Choose(true);
    if (loaned != nullptr) {
        loaned->MarkReturned();
    }
}

Media* Library::Choose(bool a_searchForLoaned) {
    size_t limit = 0;
    size_t seperator = 0;

    Context choiches{this->m_interface.SearchFor(), a_searchForLoaned};
    this->m_books.ForEach(ReturnIndexesOfMatches, (void*)&choiches);
    this->m_cds.ForEach(ReturnIndexesOfMatches, (void*)&choiches);

    if (choiches.GetIdx(BOOK) != 0) {
        ListAndIndex booksListAndIndex{&this->m_books};
        choiches.GetBooksIndexes()->ForEach(PrintNumberedOption, (void*)&booksListAndIndex);
        seperator = booksListAndIndex.Get();
    }

    limit = seperator;

    if (choiches.GetIdx(CD) != 0) {
        ListAndIndex cdsListAndIndex{&this->m_cds, seperator};
        choiches.GetCDsIndexes()->ForEach(PrintNumberedOption, (void*)&cdsListAndIndex);
        limit = cdsListAndIndex.Get();
    }

    if (limit == 0) {
        return nullptr;
    }

    size_t choiceIdx = this->m_interface.AskIdx(limit);
    if (choiceIdx >= seperator) {
        choiceIdx -= seperator;
        return this->m_cds.Get(choiches.GetCDsIndexes()->Get(choiceIdx));
    }
    return this->m_books.Get(choiches.GetBooksIndexes()->Get(choiceIdx));
}

void Library::Save() const {
    FILE *pFile = fopen(FILE_NAME, "w");
    if (pFile != NULL) {
        this->m_books.ForEach(SaveAllToFile, (void*)pFile);
        this->m_cds.ForEach(SaveAllToFile, (void*)pFile);
        fclose(pFile);
    }
}

void Library::Load() {
    Media *loaded;
    Media_t loadedMedioum;
    FILE *pFile = fopen(FILE_NAME, "r");
    if (pFile != NULL) {
        while (LoadMediaUnit(pFile, &loaded, &loadedMedioum)) {
            switch (loadedMedioum) {
            case BOOK:
                this->m_books.PushTail(loaded);
                break;
            case CD:
                this->m_cds.PushTail(loaded);
                break;
            }
        }
        fclose(pFile);
    }
}

static bool PrintAllAction(const Media* a_media, void* a_context) {
    a_media->Print();
    return true;
}

static bool PrintDetailsForMatches(const Media* a_media, void* a_searchFor) {
    if (a_media->IsNameBeginWith((char*)a_searchFor)) {
        a_media->Details();
    }
    return true;
}

static bool SaveAllToFile(const Media* a_media, void* a_fileStream) {
    a_media->Save((FILE*)a_fileStream);
    return true;
}

static bool ReturnIndexesOfMatches(const Media* a_media, void* a_context) {
    if (a_media->IsNameBeginWith(((Context*)a_context)->GetSearchKey()) && 
        a_media->IsLoaned() == ((Context*)a_context)->GetSearchForLoanedStatus()) {
        switch (a_media->Medioum()) {
        case BOOK:
            ((Context*)a_context)->GetBooksIndexes()->PushHead(((Context*)a_context)->GetIdx(BOOK));
            break;
        case CD:
            ((Context*)a_context)->GetCDsIndexes()->PushHead(((Context*)a_context)->GetIdx(CD));
            break;
        }
    }
    ((Context*)a_context)->Advance(a_media->Medioum());
    return true;
}

static bool PrintNumberedOption(size_t a_idx, void* a_listAndIndex) {
    ((ListAndIndex*)a_listAndIndex)->Advance();
    ((ListAndIndex*)a_listAndIndex)->Print(a_idx);
    return true;
}
