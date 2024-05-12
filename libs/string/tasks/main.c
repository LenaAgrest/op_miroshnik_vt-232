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
    char s[] = "    It`s     test     task     two     eighteen     lab    ";
    removeExtraSpaces(s);
    ASSERT_STRING("It`s test task two eighteen lab", s);
}

void test_digitsToStart(){
    char s[] = "Tes1t8";
    digitsToStart(s);
    ASSERT_STRING("18Test", s);
}

int main(){
    test_removeNonLetters();
    test_removeExtraSpaces();
    test_digitsToStart();
}