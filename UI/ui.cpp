#include "ui.hpp"
#include <stdio.h>
#include <stdlib.h> /* strtol */
#include "name.hpp"

#define INDEX_DIGITS_LIMIT 5
#define SCANF_FORMAT_LEN 15
#define MAX_OPTION_DIGIT_LIMIT 1

static const char *s_menuUI[OPTION_LEN] = {
    "Exit",
    "List Media",
    "Print Details For a Media Item",
    "Add a Book to Library",
    "Add a CD to Library",
    "Mark Media Item as Loaned",
    "Mark Media Item as Returned"
};

Option UI::Menu() const {
    int choose;
    char input[MAX_OPTION_DIGIT_LIMIT];
    printf("\n*** Menu ***\n\n");
    for (int i = 1; i < OPTION_LEN; ++i) {
        printf(" (%d) - %s\n", i, s_menuUI[i]);
    }
    printf(" (0) - %s\n\n", s_menuUI[0]);
    while (true) {
        AskInput("Please Insert Option: ", input, MAX_OPTION_DIGIT_LIMIT);
        choose = atoi(input);
        if (choose >= 0 && choose < OPTION_LEN) {
            break;
        } else {
            printf("Out Of Bound. Please Try Again.\n");
        }
    }
    return (Option)choose;
}

size_t UI::AskIdx(const size_t a_limit) const {
    size_t idx;
    char input[INDEX_DIGITS_LIMIT];
    while (true) {
        AskInput("\nPlease Insert Item's Index: ", input, INDEX_DIGITS_LIMIT);
        idx = (size_t)atoi(input);
        if (idx > 0 && idx <= a_limit) {
            break;
        } else {
            printf("Out Of Bound. Please Try Again.\n");
        }
    }
    return idx - 1;
}

/* Functions */

bool AskYorN(const char* a_prompt) {
    char answer;
    bool result;
    while (true)
    {    
        printf("%s - (y\\n): ", a_prompt);
        getchar(); // flush input stream
        answer = (char)getchar();
        if (answer == 'y' || answer == 'Y') {
            result = true;
            break;
        }
        if (answer == 'n' || answer == 'N') {
            result = false;
            break;
        }
        printf("Invalid Option. Please Try Again.");
    }
    putchar('\n');
    return result;
}

bool Ask(const char* a_prompt, const char* a_false, const char* a_true) {
    int answer;
    bool result;
    while (true)
    {    
        printf("%s\n\nFor %s Press (1)\nFor %s Press (2)\n\n", a_prompt, a_false, a_true);
        getchar(); // flush input stream
        answer = getchar() - (int)'0';
        if (answer == 1) {
            result = false;
            break;
        }
        if (answer == 2) {
            result = true;
            break;
        }
        printf("Invalid Option. Please Try Again.");
    }
    putchar('\n');
    return result;
}

void AskInput(const char* a_prompt, char *a_buffer, size_t a_length) {
    char format[SCANF_FORMAT_LEN] = " %";
    snprintf(format + 2, SCANF_FORMAT_LEN - 2, "%lu[^\n]s", a_length);
    printf("%s", a_prompt);
    scanf(format, a_buffer);
    putchar('\n');
}

void PrintMedia(bool a_isLoaned, const char *a_mediaDetails) {
    a_isLoaned ? printf("* ") : printf("  ");
    printf("%s\n", a_mediaDetails);
}

void PrintMediaDetails(bool a_isLoaned, const char *a_mediaDetails, const char *a_loaner) {
    PrintMedia(a_isLoaned, a_mediaDetails);
    printf("  Loaned? - ");
    fputs(a_isLoaned ? "true" : "false", stdout);
    a_isLoaned ? printf("\tLoaned To %s\n\n", a_loaner) : printf("\n\n");
}
