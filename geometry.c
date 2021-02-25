#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* pars_bracket(char* cursor, char sign); //парсинг скобок
char* pars_digit(char* cursor, double* num); //парсинг чисел
char* pars_comma(char* cursor); //парсинг запятой
bool check_eof(char* cursor);   //проверка до конца строки

int main()
{
    char str[30];
    char* cursor = str;
    char* cursor2 = str;
    double data[3];
    double x, y, radius;

    fgets(str, sizeof(str), stdin);

    while (*cursor == ' ') { //пропускаем пробелы перед словом
        cursor++;
        cursor2++;
    }
    if (isalpha(*cursor) != 0) { //ставим второй курсор на конец слова
        while (isalpha(*cursor2) != 0) {
            cursor2++;
        }
    }

    if (strncasecmp(cursor, "circle", cursor2 - cursor) != 0) {
        printf("^\n");
        printf("Error at column 0: expected 'circle'\n");
        return 0;
    }

    cursor = cursor2;

    if ((cursor = pars_bracket(cursor, '(')) == 0)
    {
        return 0;
    }
    if ((cursor = pars_digit(cursor, &x)) != 0)
    {
        data[0] = x;
    } else {
        return 0;
    }
    //    printf("x = %.1f\n", data[0]);

    if ((cursor = pars_digit(cursor, &y)) != 0)
    {
        data[1] = y;
    } else {
        return 0;
    }

    //    printf("y = %.1f\n", data[1]);

    if ((cursor = pars_comma(cursor)) == 0)
    {
        return 0;
    }

    if ((cursor = pars_digit(cursor, &radius)) != 0)
    {
        data[2] = radius;
    } else {
        return 0;
    }
    //    printf("rad = %.1f\n", data[2]);

    if ((cursor = pars_bracket(cursor, ')')) == 0)
    {
        return 0;
    }

    if (check_eof(cursor) == 0)
    {
        return 0;
    }

    return 0;
}

char* pars_bracket(char* cursor, char sign)
{
    while (*cursor != '\n') {
        if (*cursor == sign) {
            cursor++;
            return cursor;
        }
        if (*cursor == ' ') {
            cursor++;
        } else {
            printf("expected '%c'\n", sign);
            return 0;
        }
    }
    if (*cursor == '\n') {
        printf("expected '%c'\n", sign);
        return 0;
    }
    return 0;
}

char* pars_digit(char* cursor, double* num)
{
    char* end;
    while (isdigit(*cursor) == 0) {
        if (*cursor == ' ') {
            cursor++;
        } else {
            printf("expected '<double>'\n");
            return 0;
        }
    }

    if (isdigit(*cursor) != 0) {
        *num = strtod(cursor, &end);
        cursor = end;
    }
    return cursor;
}

char* pars_comma(char* cursor)
{
    while (*cursor != ',') {
        if (*cursor == ' ') {
            cursor++;
        } else {
            printf("expected ','\n");
            return 0;
        }
    }

    if (*cursor == ',') {
        cursor++;
    }

    if (*cursor != ' ') {
        printf("expected ' ' after ','\n");
        return 0;
    } else {
        cursor++;
    }
    return cursor;
}

bool check_eof(char* cursor)
{
    while (*cursor != '\n') {
        if (*cursor != ' ') {
            printf("unexpected token\n");
            return false;
        }
        cursor++;
    }
    return true;
}
