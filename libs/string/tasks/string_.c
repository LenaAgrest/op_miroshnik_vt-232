#include "string_.h"
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <memory.h>

size_t strlen_(const char *begin) {
    char *end = begin;
    while (*end != '\0')
        end++;
    return end - begin;
}

char* find(char *begin, char *end, int ch) {
while (begin != end && *begin != ch)
begin++;
return begin;
}

char* findNonSpace(char *begin) {
    while (isspace(*begin) && *begin != '\0') {
        begin++;
    }
    return begin;
}

void test_find() {
    char string[] = "lab_17";

    assert(find(string, string + 5, 'a') == string + 1);
}

void test_find_non_space() {
    char string[] = "lab_17";

    assert(findNonSpace(string) == string);
}

void test() {

test_find();
test_find_non_space();

}