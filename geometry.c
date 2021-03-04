#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct circle {
    double x[2];
    double y[2];
    double radius[2];
};

struct triangle {
    double x1[2];
    double y1[2];
    double x2[2];
    double y2[2];
    double x3[2];
    double y3[2];
    double x4[2];
    double y4[2];
};

char* parse_bracket(char* cursor, char sign); //парсинг скобок
char* parse_digit(char* cursor, double* num); //парсинг чисел
char* parse_comma(char* cursor);              //парсинг запятой
char* check_eof(char* cursor); //проверка до конца строки
char* parse_circle(char* cursor, int i, struct circle* obj_circle);
char* parse_triangle(char* cursor, int j, struct triangle* obj_triangle);

int main()
{
    struct circle obj_circle;
    struct triangle obj_triangle;

    char str[100];
    char* startcursor = str;
    char* cursor = str;
    int i = 0, j = 0;

    while (fgets(str, 100, stdin)) {
        startcursor = str;
        cursor = str;

        while (*startcursor == ' ') { //пропускаем пробелы перед словом
            startcursor++;
            cursor++;
        }
        if (isalpha(*startcursor) != 0) { //ставим второй курсор на конец слова
            while (isalpha(*cursor) != 0) {
                cursor++;
            }
        }

        if (strncasecmp(startcursor, "circle", cursor - startcursor) == 0) {
            if (parse_circle(cursor, i, &obj_circle) != 0) {
                i++;
            }
        } else {
            if (strncasecmp(startcursor, "triangle", cursor - startcursor) == 0) {
                if (parse_triangle(cursor, j, &obj_triangle) != 0) {
                    j++;
                }
            } else {
                printf("^\n");
                printf("Error at column 0: expected 'circle' or 'triangle'\n");
            }
        }
    }
    for (int k = 0; k < i; k++) {
        printf("circle (%.1f %.1f, %.1f)\n",
               obj_circle.x[k],
               obj_circle.y[k],
               obj_circle.radius[k]);
    }
    for (int k = 0; k < j; k++) {
        printf("triangle ((%.1f %.1f, %.1f %.1f, %.1f %.1f, %.1f %.1f))\n",
               obj_triangle.x1[k],
               obj_triangle.y1[k],
               obj_triangle.x2[k],
               obj_triangle.y2[k],
               obj_triangle.x3[k],
               obj_triangle.y3[k],
               obj_triangle.x4[k],
               obj_triangle.y4[k]);
    }

    return 0;
}

char* parse_circle(char* cursor, int i, struct circle* obj_circle)
{
    double x1, y1, radius1;

    if ((cursor = parse_bracket(cursor, '(')) == 0) {
        return 0;
    }
    if ((cursor = parse_digit(cursor, &x1)) != 0) {
        obj_circle->x[i] = x1;
    } else {
        return 0;
    }

    if ((cursor = parse_digit(cursor, &y1)) != 0) {
        obj_circle->y[i] = y1;
    } else {
        return 0;
    }

    if ((cursor = parse_comma(cursor)) == 0) {
        return 0;
    }

    if ((cursor = parse_digit(cursor, &radius1)) != 0) {
        obj_circle->radius[i] = radius1;
    } else {
        return 0;
    }

    if ((cursor = parse_bracket(cursor, ')')) == 0) {
        return 0;
    }

    if ((cursor = check_eof(cursor)) == 0) {
        return 0;
    }

    return cursor;
}

char* parse_triangle(char* cursor, int j, struct triangle* obj_triangle)
{
    double x1, x2, x3, x4, y1, y2, y3, y4;

    if ((cursor = parse_bracket(cursor, '(')) == 0) {
        return 0;
    }

    if ((cursor = parse_bracket(cursor, '(')) == 0) {
        return 0;
    }

    if ((cursor = parse_digit(cursor, &x1)) != 0) {
        obj_triangle->x1[j] = x1;
    } else {
        return 0;
    }

    if ((cursor = parse_digit(cursor, &y1)) != 0) {
        obj_triangle->y1[j] = y1;
    } else {
        return 0;
    }

    if ((cursor = parse_comma(cursor)) == 0) {
        return 0;
    }

    if ((cursor = parse_digit(cursor, &x2)) != 0) {
        obj_triangle->x2[j] = x2;
    } else {
        return 0;
    }

    if ((cursor = parse_digit(cursor, &y2)) != 0) {
        obj_triangle->y2[j] = y2;
    } else {
        return 0;
    }

    if ((cursor = parse_comma(cursor)) == 0) {
        return 0;
    }

    if ((cursor = parse_digit(cursor, &x3)) != 0) {
        obj_triangle->x3[j] = x3;
    } else {
        return 0;
    }

    if ((cursor = parse_digit(cursor, &y3)) != 0) {
        obj_triangle->y3[j] = y3;
    } else {
        return 0;
    }

    if ((cursor = parse_comma(cursor)) == 0) {
        return 0;
    }

    if ((cursor = parse_digit(cursor, &x4)) != 0) {
        obj_triangle->x4[j] = x4;
    } else {
        return 0;
    }

    if ((cursor = parse_digit(cursor, &y4)) != 0) {
        obj_triangle->y4[j] = y4;
    } else {
        return 0;
    }

    if ((cursor = parse_bracket(cursor, ')')) == 0) {
        return 0;
    }

    if ((cursor = parse_bracket(cursor, ')')) == 0) {
        return 0;
    }

    if ((cursor = check_eof(cursor)) == 0) {
        return 0;
    }

    return cursor;
}

char* parse_bracket(char* cursor, char sign)
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

char* parse_digit(char* cursor, double* num)
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

char* parse_comma(char* cursor)
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

char* check_eof(char* cursor)
{
    while (*cursor != '\n') {
        if (*cursor != ' ') {
            printf("unexpected token\n");
            return false;
        }
        cursor++;
    }
    return cursor;
}
