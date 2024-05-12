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

#endif