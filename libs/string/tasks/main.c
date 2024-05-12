#define ASSERT_STRING(expected, got) assertString(expected, got, \
                                                  __FILE__, __FUNCTION__, __LINE__)

#include "string_18_.c"
#include <stdio.h>
#include <assert.h>

void test_removeNonLetters()
{
    char s[] = "Te st 18 1";
    removeNonLetters(s);
    ASSERT_STRING("Test181", s);
}

void test_removeExtraSpaces()
{
    char s[] = "    It`s     test     task     two     eighteen     lab    ";
    removeExtraSpaces(s);
    ASSERT_STRING("It`s test task two eighteen lab", s);
}

void test_digitsToStart()
{
    char s[] = "Tes1t8";
    digitsToStart(s);
    ASSERT_STRING("18Test", s);
}

void test_replacesNumbersWithSpaces()
{
    char s[MAX_STRING_SIZE] = "e1up0hor2ia";
    char s1[MAX_STRING_SIZE];
    replacesNumbersWithSpaces(s, s1);
    ASSERT_STRING("e uphor  ia", s1);
}

void test_replace()
{
    char s[MAX_STRING_SIZE] = "hello world hello";
    char *word1 = "aaa";
    char *word2 = "hey";
    replace(s, word1, word2);
    ASSERT_STRING("hello world hello", s);
}

void test_areWordsOrdered()
{
    char s[] = "banana apple cherry";
    assert(areWordsOrdered(s) == 0);
}

void test_reverseWordsBag()
{
    char s[MAX_STRING_SIZE] = "privet poka";
    reverseWordsBag(s);
    printf("\n");
    // ASSERT_STRING("akop tevirp", s);
}

void test_howManyWordsPalindromes()
{
    char s[] = "tot,abcba";
    assert(howManyWordsPalindromes(s) == 2);
}

void test_mergeString()
{
    char s1[] = "a a a";
    char s2[] = "a a a";
    char result[100] = "";
    mergeStrings(s1, s2, result);
    ASSERT_STRING("a a a a a a", result);
}

void test_reverseWords()
{
    char p[MAX_STRING_SIZE] = "a a a";
    reverseWords(p);
    ASSERT_STRING("a a a", p);
}

void test_getWordBeforeFirstWordWithA()
{
    WordDescriptor word;
    char s1[] = "";
    assert(getWordBeforeFirstWordWithA(s1, &word) == EMPTY_STRING);
    char s2[] = "ABC";
    assert(getWordBeforeFirstWordWithA(s2, &word) == FIRST_WORD_WITH_A);
    char s3[] = "BC A";
    assert(getWordBeforeFirstWordWithA(s3, &word) == WORD_FOUND);
    char s4[] = "B Q WE YR OW  IUWR";
    assert(getWordBeforeFirstWordWithA(s4, &word) == NOT_FOUND_A_WORD_WITH_A);
}

void test_lastWordInFirstStringInSecondString()
{
    char s1_1[] = "A B C D E";
    char s2_1[] = "Y U";
    WordDescriptor word1 = lastWordInFirstStringInSecondString(s1_1, s2_1);
    char str1[MAX_WORD_SIZE];
    wordDescriptorToString(word1, str1);
    ASSERT_STRING(str1, "");
}

int main()
{
    test_removeNonLetters();
    test_removeExtraSpaces();
    test_digitsToStart();
    test_replacesNumbersWithSpaces();
    test_replace();
    test_areWordsOrdered();
    test_reverseWordsBag();
    test_howManyWordsPalindromes();
    test_mergeString();
    test_reverseWords();
    test_getWordBeforeFirstWordWithA();
    test_lastWordInFirstStringInSecondString();
}