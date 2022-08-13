#include "ui.hpp"
#include <stdio.h>
#include "name.hpp"

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
    printf("\n*** Menu ***\n\n");
    for (int i = 1; i < OPTION_LEN; ++i) {
        printf(" (%d) - %s\n", i, s_menuUI[i]);
    }
    printf(" (0) - %s\n\n", s_menuUI[0]);
    while (true) {
        printf("Please Insert Option: ");
        scanf("%d", &choose);
        if (choose >= 0 && choose < OPTION_LEN) {
            break;
        } else {
            printf("Out Of Bound. Please Try Again.\n");
        }
    }
    putchar('\n');
    return (Option)choose;
}

size_t UI::AskIdx(const size_t a_limit) const {
    size_t idx;
    while (true) {
        printf("\nPlease Insert Item's Index: ");
        scanf(" %3lu", &idx);
        if (idx > 0 && idx <= a_limit) {
            break;
        } else {
            printf("Out Of Bound. Please Try Again.\n");
        }
    }
    putchar('\n');
    return idx - 1;
}

const char* UI::SearchFor() const {
    char *key = new char[MAX_NAME_LEN];
    printf("Please Insert Search Key: ");
// ! refactor
    scanf(" %30[^\n]s", key);
    putchar('\n');
    return key;
}

bool AskYorN(const char* a_prompt) {
    char answer;
    bool result;
    while (true)
    {    
        printf("%s - (y\\n) - ", a_prompt);
        scanf("%c", &answer);
        if (answer == 'y' || answer == 'Y') {
            result = true;
            break;
        }
        if (answer == 'n' || answer == 'N') {
            result = false;
            break;
        }
    }
    putchar('\n');
    return result;
}

bool Ask(const char* a_prompt, const char* a_false, const char* a_true) {
    int answer;
    bool result;
    while (true)
    {    
        printf("%s\n\nFor %s Press (1)\nFor %s Press (2)\n", a_prompt, a_false, a_true);
        scanf("%d", &answer);
        if (answer == 1) {
            result = false;
            break;
        }
        if (answer == 2) {
            result = true;
            break;
        }
    }
    putchar('\n');
    return result;
}