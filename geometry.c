#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* parsing_digit1(char* cursor, double* x);
char* parsing_digit2(char* cursor, double* y);
char* parsing_digit3(char* cursor, double* radius);
char* parsing_comma(char* cursor);
bool search_brecket(char* cursor);  //поиск '('
bool search_comma(char* cursor);    //поиск ','
bool search_brecket2(char* cursor); //поиск ')'
bool check_eof(char* cursor); //проверка до конца строки

int main()
{
    char str[30];
    char* cursor = str;
    char* cursor2 = str;
    double data[3];
    double x, y, radius;

    fgets(str, sizeof(str), stdin);

    while (*cursor == ' ') {
        cursor++;
        cursor2++;
    }
    if (isalpha(*cursor) != 0) {
        while (isalpha(*cursor2) != 0) {
            cursor2++;
        }
    }

    if (strncasecmp(cursor, "circle", cursor2 - cursor) != 0) {
        printf("^\n");
        printf("Error at column 0: expected 'circle'\n");
    } else {
        cursor = cursor2;

        if (search_brecket(cursor) == 0) //поиск '('
        {
            return 0;
        }

        if ((cursor = parsing_digit1(cursor, &x)) != 0) //парсинг первого числа
        {
            data[0] = x;
        } else {
            return 0;
        }
//         printf("x = %.1f\n", data[0]);

        if ((cursor = parsing_digit2(cursor, &y)) != 0) //парсинг второго числа
        {
            data[1] = y;
        } else {
            return 0;
        }
//         printf("y = %.1f\n", data[1]);

        if (search_comma(cursor) == 0) //поиск ','
        {
            return 0;
        }

        if ((cursor = parsing_comma(cursor)) == 0) //парсинг запятой
        {
            return 0;
        }

        if ((cursor = parsing_digit3(cursor, &radius)) != 0) //парсинг третьего числа
        {
            data[2] = radius;
        } else {
            return 0;
        }
//         printf("rad = %.1f\n", data[2]);

        if (search_brecket2(cursor) == 0) //поиск ')'
        {
            return 0;
        }
        if (check_eof(cursor) == 0) //проверка конца строки
        {
            return 0;
        }
    }
    return 0;
}

bool search_brecket(char* cursor)
{
    int flag = 0;

    while (*cursor != 10) {
        if (*cursor == '(') {
            flag = 1;
            break;
        }
        cursor++;
    }
    if (flag == 0) {
        printf("expected '('\n");
        return false;
    }
    return true;
}

char* parsing_digit1(char* cursor, double* x)
{
    char* end;
    while (isdigit(*cursor) == 0) {
        if ((*cursor == ' ') || (*cursor == '(')) {
            cursor++;
        } else {
            printf("expected '<double>'\n");
            return 0;
        }
    }

    if (isdigit(*cursor) != 0) {
        *x = strtod(cursor, &end);
        cursor = end;
    }
    return cursor;
}

char* parsing_digit2(char* cursor, double* y)
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
        *y = strtod(cursor, &end);
        cursor = end;
    }
    return cursor;
}

bool search_comma(char* cursor)
{
    int flag = 0;

    while (*cursor != 10) {
        if (*cursor == ',') {
            flag = 1;
            break;
        }
        cursor++;
    }
    if (flag == 0) {
        printf("expected ','\n");
        return false;
    }
    return true;
}

char* parsing_comma(char* cursor)
{
    while (*cursor != ',') {

        if (*cursor == ' ') {
            cursor++;
        } else {
            printf("expected '<double>'\n");
            return 0;
        }
    }

    if (*cursor == ',')
    {
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

char* parsing_digit3(char* cursor, double* radius)
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
        *radius = strtod(cursor, &end);
        cursor = end;
    }
    return cursor;
}

bool search_brecket2(char* cursor)
{
    int flag = 0;

    while (*cursor != 10) {
        if (*cursor == ')') {
            flag = 1;
            break;
        }
        cursor++;
    }
    if (flag == 0) {
        printf("expected ')'\n");
        return false;
    }
    return true;
}

bool check_eof(char* cursor)
{
    while (*cursor != ')') {

        if (*cursor == ' ') {
            cursor++;
        } else {
            printf("expected '<double>'\n");
            return false;
        }
    }

    if (*cursor == ')') {
        cursor++;
        if (*cursor == 10) {
            return true;
        }
    }

    while (*cursor != 10) {
        if (*cursor != ' ') {
            printf("unexpected token\n");
            return false;
        }
        cursor++;
    }
    return true;
}
