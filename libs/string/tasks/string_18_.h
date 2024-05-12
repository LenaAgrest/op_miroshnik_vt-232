#include "string_.h"
#include <stdbool.h>

#ifndef LAB18__H
#define LAB18__H

#define MAX_STRING_SIZE 100
#define MAX_N_WORDS_IN_STRING 100
#define MAX_WORD_SIZE 20
#define MAX_WORDS 100

typedef struct WordDescriptor {
    char *begin; // позиция начала слова
    char *end; // позиция первого символа, после последнего символа слова
} WordDescriptor;

typedef struct BagOfWords {
    WordDescriptor words[MAX_N_WORDS_IN_STRING];
    size_t size;
} BagOfWords;

typedef enum WordBeforeFirstWordWithAReturnCode {
    FIRST_WORD_WITH_A,
    NOT_FOUND_A_WORD_WITH_A,
    WORD_FOUND,
    EMPTY_STRING
} WordBeforeFirstWordWithAReturnCode;

char* getEndOfString(char *s);

void removeNonLetters(char *s);

void removeExtraSpaces(char *s);

int getWord(char *beginSearch, WordDescriptor *word);

void reversedDigitToStart(WordDescriptor word);

void digitToStart(WordDescriptor word);

void digitsToStart(char *s);

int getWordReverse(char *rbegin, char *rend, WordDescriptor *word);

void replacesNumbersWithSpaces(char *input, char *output);

void replace(char *source, char *w1, char *w2);

void replace(char *source, char *w1, char *w2);

bool areWordsEqual(WordDescriptor w1, WordDescriptor w2);

char* strpbrk_(const char* str, const char* delim);

char* strtok_(char* str, const char* delim);

bool areWordsOrdered(char *s);

void getBagOfWords(BagOfWords *bag, char *s);

void reverseWordsBag(char *s);

bool isWordPalindrome(char *begin, char *end);

int howManyWordsPalindromes(char *s);

void strcpy_(char *dest, const char *src);

char *strchr_(const char *str, int c);

char* my_strtok_r(char* str, const char* delim, char** saveptr);

void mergeStrings(char *str1, char *str2, char *result);

void reverse(char *begin, char *end);

void reverseWords(char *str);

void printWordBeforeFirstWordWithA(char *s);

WordBeforeFirstWordWithAReturnCode getWordBeforeFirstWordWithA(char *s, WordDescriptor *w);

int strncmp_(const char *s1, const char *s2, int n);

char *strncpy_(char *destination, const char *source, int num);

void wordDescriptorToString(WordDescriptor word, char *destination);

BagOfWords createBagOfWordsFromString(char *s);

int isWordInBagOfWords(WordDescriptor word, BagOfWords bag);

WordDescriptor lastWordInFirstStringInSecondString(char *s1, char *s2);

bool hasDuplicateWords(char* sentence);

char* sortWord(char *word);

char *my_strdup(const char *str);

int findPairWithSameLetters(char *str);

char *strcat_(char *dest, const char *src);

void removeLastSpace(char *str);

char* getWordsDifferentFromLast(char *str);

#endif