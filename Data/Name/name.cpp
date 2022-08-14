#include "name.hpp"
#include <string.h>
#include <stdio.h> /* printf */
#include <time.h>
#include "ui.hpp"

static char* GenerateName();
static char* CreateConcatenated(const char* a_firstName, const char* a_secondName);
static char* Duplicate(const char *a_str);

Name::Name()
: m_name(GenerateName()) 
{
}

Name::Name(const char *a_name)
: m_name(Duplicate(a_name)) 
{
}

Name::Name(const Name &a_other)
: m_name(Duplicate(a_other.m_name)) 
{
}

Name::Name(const char *a_prompt, bool a_stdin) {
    if (a_stdin) {
        char *newName = new char[MAX_NAME_LEN];
        AskInput(a_prompt, newName, MAX_NAME_LEN);
        this->m_name = Duplicate(newName);
        delete[] newName;
    } else {
        this->m_name = Duplicate(a_prompt);
    }
}

Name &Name::operator=(const Name &a_other) {
    delete[] this->m_name;
    this->m_name = Duplicate(a_other.m_name);
    return *this;
}

Name::~Name() {
    delete[] this->m_name;
}

bool Name::operator==(const Name &a_other) const noexcept {
    return strcmp(this->m_name,a_other.m_name) == 0;
}

Name &Name::operator+=(const Name &a_other) {
    char *newName = CreateConcatenated(this->m_name, a_other.m_name);
    delete[] this->m_name;
    this->m_name = newName;
    return *this;
}

Name Name::operator+(const Name &a_other) const {
    Name result(*this);
    result += a_other;
    return result;
}

const char *Name::GetName() const noexcept {
    return this->m_name;
}

void Name::ReplaceAllLetters(char a_c) noexcept {
    for(int i = 0 ; this->m_name[i] != '\0' ; ++i) {
        this->m_name[i] = a_c;
    }
}

static char *GenerateName() {
    time_t rawtime;
    struct tm* timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    return Duplicate(asctime(timeinfo));
}

static char *CreateConcatenated(const char* a_first, const char* a_second) {
    size_t lenF = strlen(a_first);
    size_t lenS = strlen(a_second);
    size_t bufferS = lenF + lenS + sizeof('\0');
    char *newName = new char[bufferS];
    memcpy(newName, a_first, lenF);
    memcpy(&newName[lenF], a_second, lenS);
    newName[bufferS] = '\0';
    return newName;
}

static char *Duplicate(const char *a_str) {
    return strcpy(new char[strlen(a_str)+sizeof('\0')] , a_str);
}
