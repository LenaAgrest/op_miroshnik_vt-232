#include "string_.h"
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <memory.h>

size_t strlen_(const char *str) {
    const char *s = str;
    while (*s)
        s++;
    return s - str;
}

char *find(char *begin, char *end, int ch)
{
    while (begin != end && *begin != ch)
        begin++;
    return begin;
}

char *findNonSpace(char *begin)
{
    while (isspace(*begin) && *begin != '\0')
    {
        begin++;
    }
    return begin;
}

char *findSpace(char *begin)
{
    while (!isspace(*begin) && *begin != '\0')
    {
        begin++;
    }
    return begin;
}

char *findNonSpaceReverse(char *rbegin, const char *rend)
{
    while (rbegin >= rend && isspace(*rbegin))
    {
        rbegin--;
    }
    return rbegin;
}

char *findSpaceReverse(char *rbegin, const char *rend)
{
    while (rbegin >= rend && !isspace(*rbegin))
    {
        rbegin--;
    }
    return rbegin;
}

int strcmp_(const char *lhs, const char *rhs)
{
    while (*lhs == *rhs && *lhs != '\0' && *rhs != '\0')
    {
        lhs++;
        rhs++;
    }
    return *lhs - *rhs;
}

char *copy(const char *beginSource, const char *endSource, char *beginDestination)
{
    size_t size = endSource - beginSource;
    memcpy(beginDestination, beginSource, size);
    *(beginDestination + size) = '\0';

    return beginDestination + size;
}

char *copyIf(char *beginSource, const char *endSource, char *beginDestination, int (*f)(int))
{
    while (beginSource != endSource)
    {
        if (f(*beginSource))
        {
            *beginDestination = *beginSource;
            beginDestination++;
        }
        beginSource++;
    }
    *beginDestination = '\0';

    return beginDestination;
}

char *copyIfReverse(char *rbeginSource, const char *rendSource, char *beginDestination, int (*f)(int))
{
    char *beginDestination_ = beginDestination;
    while (rbeginSource >= rendSource)
    {
        if (f(*rbeginSource))
        {
            *beginDestination_ = *rbeginSource;
            beginDestination_++;
        }
        rbeginSource--;
    }
    *beginDestination_ = '\0';

    return beginDestination_;
}

int is_h(char s)
{
    return s == 'h' || s == 'w';
}

char *getEndOfString(char *s)
{
    char *end = s;
    while (*end != '\0')
    {
        end++;
    }
    return end;
}











void test_find()
{
    char string[] = "lab_17";

    assert(find(string, string + 5, 'a') == string + 1);
}

void test_find_non_space()
{
    char string[] = "lab_17";

    assert(findNonSpace(string) == string);
}

void test_find_space()
{
    char string[] = " ab_17";

    assert(findSpace(string) == string);
}

void test_find_non_space_reverse()
{
    char string[] = "lab_17";

    assert(findNonSpaceReverse(string + 4, string) == string + 4);
}

void test_find_space_reverse()
{
    char string[] = "lab_17";

    assert(findSpaceReverse(string + 3, string) == string - 1);
}

void test_strcmp_()
{
    char string1[] = "lab_17";
    char string2[] = "laba_17";

    assert(strcmp_(string1, string2) < 0);
}
int isLetter(int c)
{
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

void test_copyIf()
{
    char source[] = "Hello, world!";
    char destination[20];

    char *endDestination = copyIf(source, source + sizeof(source), destination, isLetter);

    assert(endDestination == destination + 10);

    for (int i = 0; i < 10; ++i)
    {
        assert(destination[i] == "Helloworld"[i]);
    }
}

void test()
{

    test_find();
    test_find_non_space();
    test_find_space();
    test_find_non_space_reverse();
    test_find_space_reverse();
    test_strcmp_();
    test_copyIf();
}