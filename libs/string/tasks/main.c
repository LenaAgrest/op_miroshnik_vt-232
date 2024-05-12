#define ASSERT_STRING(expected, got) assertString(expected, got, \
__FILE__, __FUNCTION__, __LINE__)

#include "string_18_.c"
#include <stdio.h>
#include <assert.h>

void test_removeNonLetters(){
    char s[] = "Te st 18 1";
    removeNonLetters(s);
    ASSERT_STRING("Test181", s);
}

void test_removeExtraSpaces(){
    char s[] = "    Everyone     is     friends     with     each     other    ";
    removeExtraSpaces(s);
    ASSERT_STRING("Everyone is friends with each other", s);
}

int main(){
    test_removeNonLetters();
    test_removeExtraSpaces();
}