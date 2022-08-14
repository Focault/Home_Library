#ifndef HOMELIBRARY_UI_H
#define HOMELIBRARY_UI_H

#include <stddef.h>

enum Option {
    EXIT,
    LIST,
    PRINT_DETAILS,
    ADD_BOOK,
    ADD_CD,
    MARK_LOANED,
    MARK_RETURNED,
    OPTION_LEN
};

class UI {
public:
    explicit UI() = default;
    ~UI() = default;

    Option Menu() const;
    size_t AskIdx(const size_t a_limit) const;

};

bool AskYorN(const char* a_prompt);

bool Ask(const char* a_prompt, const char* a_false, const char* a_true);

void AskInput(const char* a_prompt, char *a_buffer, size_t a_length);

void PrintMedia(bool a_isLoaned, const char *a_mediaDetails);

void PrintMediaDetails(bool a_isLoaned, const char *a_mediaDetails, const char *a_loaner);

#endif /* HOMELIBRARY_UI_H */