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

// удаляет из строки все пробельные символы
void removeNonLetters(char *s)
{
    char *endSource = getEndOfString(s);
    char *destination = copyIf(s, endSource, s, isgraph);
    *destination = '\0';
}

// функция тестирования, которая даёт информацию о том, где именно произошла ошибка
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
// преобразовывает слово таким образом, чтобы цифры были перенесены //в начало слова и изменить порядок следования цифр в слове на обратный
void reversedDigitToStart(WordDescriptor word)
{
    char *endStringBuffer = copy(word.begin, word.end, _stringBuffer);
    char *recPosition = copyIfReverse(endStringBuffer - 1, _stringBuffer - 1, word.begin, isdigit);
    copyIf(_stringBuffer, endStringBuffer, recPosition, isalpha);
}
// преобразовывает слово таким образом, чтобы цифры были перенесены в начало слова
void digitToStart(WordDescriptor word)
{
    char *endStringBuffer = copy(word.begin, word.end, _stringBuffer);
    char *recPosition = copyIf(_stringBuffer, endStringBuffer, word.begin, isdigit);
    copyIf(_stringBuffer, endStringBuffer, recPosition, isalpha);
}
// преобразовывает строку таким образом, чтобы цифры каждого слова были //перенесены в начало слова без изменения порядка следования их в слове, //буквы перенесены в конец слова
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
// возвращает значение 0, если слово не было считано, в противном //случае будет возвращено значение 1 и в переменную word типа WordDescriptor //будут записаны позиции начала слова, и первого символа конца слова
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