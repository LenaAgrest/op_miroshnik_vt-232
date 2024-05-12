#include "string_18_.h"
#include "string_.c"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <memory.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>

char _stringBuffer[MAX_STRING_SIZE + 1];
BagOfWords _bag;
BagOfWords _bag2;

void removeNonLetters(char *s)
{
    char *endSource = getEndOfString(s);
    char *destination = copyIf(s, endSource, s, isgraph);
    *destination = '\0';
}

void assertString(const char *expected, char *got, char const *fileName, char const *funcName, int line)
{
    if (strcmp_(expected, got))
    {
        fprintf(stderr, "File %s\n", fileName);
        fprintf(stderr, "%s - failed on line %d\n", funcName, line);
        fprintf(stderr, "Expected: \"%s\"\n", expected);
        fprintf(stderr, "Got: \"%s\"\n\n", got);
    }
    else
    {
        fprintf(stderr, "%s - OK\n", funcName);
    }
}

void removeExtraSpaces(char *s)
{
    char *begin = s;
    char *destination = begin;
    char last = *begin;

    while (*begin != '\0')
    {
        if (*begin != last || last != ' ')
        {
            *destination++ = *begin;
        }

        last = *begin++;
    }

    if (last == ' ')
    {
        destination--;
    }

    *destination = '\0';
}

int getWord(char *beginSearch, WordDescriptor *word)
{
    word->begin = findNonSpace(beginSearch);
    if (*word->begin == '\0')
    {
        return 0;
    }
    word->end = findSpace(word->begin);
    return 1;
}

void reversedDigitToStart(WordDescriptor word)
{
    char *endStringBuffer = copy(word.begin, word.end, _stringBuffer);
    char *recPosition = copyIfReverse(endStringBuffer - 1, _stringBuffer - 1, word.begin, isdigit);
    copyIf(_stringBuffer, endStringBuffer, recPosition, isalpha);
}

void digitToStart(WordDescriptor word)
{
    char *endStringBuffer = copy(word.begin, word.end, _stringBuffer);
    char *recPosition = copyIf(_stringBuffer, endStringBuffer, word.begin, isdigit);
    copyIf(_stringBuffer, endStringBuffer, recPosition, isalpha);
}

void digitsToStart(char *s)
{
    char *beginSearch = s;
    WordDescriptor word;
    while (getWord(beginSearch, &word))
    {
        digitToStart(word);
        beginSearch = word.end;
    }
}

int getWordReverse(char *rbegin, char *rend, WordDescriptor *word)
{
    word->end = findNonSpaceReverse(rbegin, rend);
    if (*word->begin == *rend)
    {
        return 0;
    }
    word->begin = findSpaceReverse(word->end, rend);
    word->begin++;
    return 1;
}

void replacesNumbersWithSpaces(char *input, char *output) {
    int i = 0, j = 0;

    while (input[i] != '\0') {
        if (isdigit(input[i])) {
            int numSpaces = input[i] - '0';

            for (int k = 0; k < numSpaces && j < MAX_STRING_SIZE-1; k++) {
                output[j++] = ' ';
            }
        } else if (j < MAX_STRING_SIZE-1) {
            output[j++] = input[i];
        }

        i++;
    }

    output[j] = '\0';
}

void replace(char *source, char *w1, char *w2){
    size_t w1Size = strlen_(w1);
    size_t w2Size = strlen_(w2);

    WordDescriptor word1 = {w1, w1 + w1Size};
    WordDescriptor word2 = {w2, w2 + w2Size};

    char *readPtr, *recPtr;

    if (w1Size >= w2Size){
        readPtr = source;
        recPtr = source;
    }else{
        copy(source, getEndOfString(source), _stringBuffer);

        readPtr = _stringBuffer;
        recPtr = source;
    }

    while (*readPtr != '\0') {
        if (memcmp(readPtr, w1, w1Size) == 0) {
            for (int i = 0; i < w2Size; ++i) {
                *recPtr = w2[i];

                recPtr++;
            }

            readPtr += w1Size;

        } else {
            *recPtr = *readPtr;

            readPtr++;
            recPtr++;
        }
    }

    *recPtr = '\0';
}

bool areWordsEqual(WordDescriptor w1, WordDescriptor w2) {
    int len1 = w1.end - w1.begin;
    int len2 = w2.end - w2.begin;

    if (len1 != len2) {
        return 0;
    }

    for (int i = 0; i < len1; i++) {
        if (w1.begin[i] != w2.begin[i]) {
            return 0;
        }
    }

    return 1;
}

char* strpbrk_(const char* str, const char* delim) {
    const char* ptr = str;

    while (*ptr != '\0') {
        const char* d = delim;

        while (*d != '\0') {
            if (*ptr == *d) {
                return (char*)ptr;
            }

            d++;
        }

        ptr++;
    }

    return NULL;
}

char* strtok_(char* str, const char* delim) {
    static char* savedToken = NULL;

    if (str != NULL) {
        savedToken = str;
    }

    if (savedToken == NULL) {
        return NULL;
    }

    char* tokenStart = savedToken;
    char* tokenEnd = strpbrk_(savedToken, delim);

    if (tokenEnd != NULL) {
        *tokenEnd = '\0';

        savedToken = tokenEnd + 1;
    } else {
        savedToken = NULL;
    }

    return tokenStart;
}

bool areWordsOrdered(char *s) {
    int len = strlen_(s);
    int words = 1;

    for (int i = 0; i < len; i++) {
        if (s[i] == ' ') {
            words++;
        }
    }

    char *word1, *word2;

    word1 = strtok_(s, " ");

    for (int i = 1; i < words; i++) {
        word2 = strtok_(NULL, " ");

        if (strcmp(word1, word2) > 0) {
            return 0;
        }
        word1 = word2;
    }

    return 1;
}

void getBagOfWords(BagOfWords *bag, char *s) {
    char *token = strtok_(s, " ");
    int wordCount = 0;

    while (token != NULL) {
        int wordLen = strlen_(token);

        bag->words[wordCount].begin = token;
        bag->words[wordCount].end = token + wordLen;

        wordCount++;
        token = strtok_(NULL, " ");
    }

    bag->size = wordCount;
}

void reverseWordsBag(char *s) {
    getBagOfWords(&_bag, s);

    for (int i = _bag.size - 1; i >= 0; i--) {
        for (char *ptr = _bag.words[i].end - 1; ptr >= _bag.words[i].begin; ptr--) {
            printf("%c", *ptr);
        }

        printf(" ");
    }
}

bool isWordPalindrome(char *begin, char *end) {
    end--;

    while (end - begin > 0) {
        if (*begin != *end) {
            return 0;
        }

        begin++;
        end--;
    }

    return 1;
}

int howManyWordsPalindromes(char *s) {
    char *endS = getEndOfString(s);
    char *beginSearch = findNonSpace(s);

    int countPalindromes = 0;

    char *commaPos = find(beginSearch, endS, ',');

    bool lastComma = *commaPos == '\0' && endS - beginSearch != 0;

    while (*commaPos != '\0' || lastComma) {
        beginSearch = findNonSpace(beginSearch);
        countPalindromes += isWordPalindrome(beginSearch, commaPos);
        beginSearch = commaPos + 1;

        if (lastComma) {
            break;
        }

        commaPos = find(beginSearch, endS, ',');
        lastComma = *commaPos == '\0';
    }

    return countPalindromes;
}
