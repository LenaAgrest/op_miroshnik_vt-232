#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define OUTPUT_FILE "output.txt"
// Функция для перенаправления вывода в файл
void redirect_stdout_to_file(const char *filename) {
    FILE *file = freopen(filename, "w", stdout);
    if (file == NULL) {
        perror("Ошибка перенаправления stdout в файл");
        exit(EXIT_FAILURE);
    }
}
// Функция для восстановления стандартного вывода
void restore_stdout() {
    fflush(stdout);
    FILE *file = freopen("C:\\Users\\wwwri\\files\\ekz.txt", "w", stdout);
    if (file == NULL) {
        perror("Ошибка восстановления stdout");
        exit(EXIT_FAILURE);
    }
}
// Функция для автоматического тестирования корректности вывода
int test_output(const char *filename, const char *expected_output) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Ошибка открытия файла для чтения");
        return 0;
    }
    char buffer[1024];
    fread(buffer, sizeof(char), sizeof(buffer) - 1, file);
    buffer[sizeof(buffer) - 1] = '\0'; // Добавление нулевого символа окончания строки

    fclose(file);

    return strcmp(buffer, expected_output) == 0;
}

int main() {
SetConsoleOutputCP(CP_UTF8);
    // Ожидаемый вывод
    const char *expected_output = "Hello, world!\nThis is a test.\n";

    // Перенаправление стандартного вывода в файл
    redirect_stdout_to_file(OUTPUT_FILE);

    // Производим вывод строк
    printf("Hello, world!\n");
    printf("This is a test.\n");

    // Восстанавливаем стандартный вывод
    restore_stdout();

    // Проверка корректности вывода
    if (test_output(OUTPUT_FILE, expected_output)) {
        printf("Тест пройден успешно.\n");
    } else {
        printf("Тест не пройден.\n");
    }

    return 0;
}
