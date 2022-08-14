#ifndef HOMELIBRARY_NAME_H
#define HOMELIBRARY_NAME_H

namespace experis {

#define MAX_NAME_LEN 30
#define MAX_NAME_LEN_DIGIT_LIMIT = 2

class Name {
public:
    explicit Name();
    explicit Name(const char *a_name);
    explicit Name(const char *a_prompt, bool a_stdin);
    Name(const Name &a_other);
    Name &operator=(const Name &a_other);
    ~Name();

    bool operator==(const Name &a_other) const noexcept;
    Name &operator+=(const Name &a_other);
    Name operator+(const Name &a_other) const;
    const char *GetName() const noexcept;
    void ReplaceAllLetters(char a_c) noexcept;

private:
    char *m_name;
};

} // experis

#endif /* HOMELIBRARY_NAME_H */
