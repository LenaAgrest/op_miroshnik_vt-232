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