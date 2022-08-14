#include "library.hpp"
#include <stdio.h>
#include "list.hpp"
#include "libraryutilities.hpp"
#include "media.hpp"
#include "ui.hpp"

namespace experis {

#define FILE_NAME "Data/Memory.DATA"

static bool PrintAllAction(Media* a_media, void* a_context);
static bool PrintDetailsForMatches(Media* a_media, void* a_searchFor);
static bool SaveAllToFile(Media* a_media, void* a_fileStream);
static bool ReturnIndexesOfMatches(Media* a_media, void* a_context);
static bool PrintNumberedOption(size_t a_idx, void* a_listAndIndex);


Library::Library() 
: m_books(true)
, m_cds(true)
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
    char searchKey[MAX_NAME_LEN];
    AskInput("Please Insert Search Key: ", searchKey, MAX_NAME_LEN);
    this->m_books.ForEach(PrintDetailsForMatches, (void*)searchKey);
    this->m_cds.ForEach(PrintDetailsForMatches, (void*)searchKey);
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

    SearchContext choiches{a_searchForLoaned};
    this->m_books.ForEach(ReturnIndexesOfMatches, (void*)&choiches);
    this->m_cds.ForEach(ReturnIndexesOfMatches, (void*)&choiches);

    if (choiches.GetIdx(BOOK) != 0) {
        ListAndIndex booksListAndIndex{&this->m_books};
        choiches.GetBooksIndexes().ForEach(PrintNumberedOption, (void*)&booksListAndIndex);
        seperator = booksListAndIndex.Get();
    }

    limit = seperator;

    if (choiches.GetIdx(CD) != 0) {
        ListAndIndex cdsListAndIndex{&this->m_cds, seperator};
        choiches.GetCDsIndexes().ForEach(PrintNumberedOption, (void*)&cdsListAndIndex);
        limit = cdsListAndIndex.Get();
    }

    if (limit == 0) {
        return nullptr;
    }

    size_t choiceIdx = this->m_interface.AskIdx(limit);
    if (choiceIdx >= seperator) {
        choiceIdx -= seperator;
        return this->m_cds.Get(choiches.GetCDsIndexes().Get(choiceIdx));
    }
    return this->m_books.Get(choiches.GetBooksIndexes().Get(choiceIdx));
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

/* Static Functions */

static bool PrintAllAction(Media* a_media, void* a_context) {
    a_media->Print();
    return true;
}

static bool PrintDetailsForMatches(Media* a_media, void* a_searchFor) {
    if (a_media->IsNameBeginWith((char*)a_searchFor)) {
        a_media->Details();
    }
    return true;
}

static bool SaveAllToFile(Media* a_media, void* a_fileStream) {
    a_media->Save((FILE*)a_fileStream);
    return true;
}

static bool ReturnIndexesOfMatches(Media* a_media, void* a_context) {
    if (a_media->IsNameBeginWith(((SearchContext*)a_context)->GetSearchKey()) && 
        a_media->IsLoaned() == ((SearchContext*)a_context)->m_searchForLoaned) {
        switch (a_media->Medioum()) {
        case BOOK:
            ((SearchContext*)a_context)->GetBooksIndexes().PushHead(((SearchContext*)a_context)->GetIdx(BOOK));
            break;
        case CD:
            ((SearchContext*)a_context)->GetCDsIndexes().PushHead(((SearchContext*)a_context)->GetIdx(CD));
            break;
        }
    }
    ((SearchContext*)a_context)->Advance(a_media->Medioum());
    return true;
}

static bool PrintNumberedOption(size_t a_idx, void* a_listAndIndex) {
    ((ListAndIndex*)a_listAndIndex)->Advance();
    ((ListAndIndex*)a_listAndIndex)->Print(a_idx);
    return true;
}

} // experis
