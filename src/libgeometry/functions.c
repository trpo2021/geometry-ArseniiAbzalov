#include "libgeometry/functions.h"
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PI 3.14
#define SIZE_ARR_STRUCT 4

double calc_perimeter_circle(struct figure_circle* circle, int k)
{
    return 2 * PI * circle->radius[k];
}

double calc_square_circle(struct figure_circle* circle, int k)
{
    return PI * pow(circle->radius[k], 2);
}

double calc_perimeter_triangle(struct figure_triangle* triangle, int h)
{
    if ((triangle->x1[h] != triangle->x4[h])
        || (triangle->y1[h] != triangle->y4[h])) {
        printf("uncorrect triangle\n");
        return 0;
    }
    double a, b, c;
    a
            = sqrt((pow((triangle->x2[h] - triangle->x1[h]), 2))
                   + (pow((triangle->y2[h] - triangle->y1[h]), 2)));
    b
            = sqrt((pow((triangle->x3[h] - triangle->x2[h]), 2))
                   + (pow((triangle->y3[h] - triangle->y2[h]), 2)));
    c
            = sqrt((pow((triangle->x1[h] - triangle->x3[h]), 2))
                   + (pow((triangle->y1[h] - triangle->y3[h]), 2)));

    return a + b + c;
}

double calc_square_triangle(struct figure_triangle* triangle, int h)
{
    double a, b, c, p;
    a
            = sqrt((pow((triangle->x2[h] - triangle->x1[h]), 2))
                   + (pow((triangle->y2[h] - triangle->y1[h]), 2)));
    b
            = sqrt((pow((triangle->x3[h] - triangle->x2[h]), 2))
                   + (pow((triangle->y3[h] - triangle->y2[h]), 2)));
    c
            = sqrt((pow((triangle->x1[h] - triangle->x3[h]), 2))
                   + (pow((triangle->y1[h] - triangle->y3[h]), 2)));

    p = (a + b + c) / 2;
    return sqrt((p * (p - a) * (p - b) * (p - c)));
}

static char* parse_bracket(char* cursor, char sign)
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

static char* parse_digit(char* cursor, double* num)
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

static char* parse_comma(char* cursor)
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

static char* check_eof(char* cursor)
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

char* parse_circle(char* cursor, int i, struct figure_circle* circle)
{
    double x1, y1, radius1;

    if ((cursor = parse_bracket(cursor, '(')) == 0) {
        return 0;
    }
    if ((cursor = parse_digit(cursor, &x1)) != 0) {
        circle->x[i] = x1;
    } else {
        return 0;
    }

    if ((cursor = parse_digit(cursor, &y1)) != 0) {
        circle->y[i] = y1;
    } else {
        return 0;
    }

    if ((cursor = parse_comma(cursor)) == 0) {
        return 0;
    }

    if ((cursor = parse_digit(cursor, &radius1)) != 0) {
        circle->radius[i] = radius1;
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

char* parse_triangle(char* cursor, int j, struct figure_triangle* triangle)
{
    double x1, x2, x3, x4, y1, y2, y3, y4;

    if ((cursor = parse_bracket(cursor, '(')) == 0) {
        return 0;
    }

    if ((cursor = parse_bracket(cursor, '(')) == 0) {
        return 0;
    }

    if ((cursor = parse_digit(cursor, &x1)) != 0) {
        triangle->x1[j] = x1;
    } else {
        return 0;
    }

    if ((cursor = parse_digit(cursor, &y1)) != 0) {
        triangle->y1[j] = y1;
    } else {
        return 0;
    }

    if ((cursor = parse_comma(cursor)) == 0) {
        return 0;
    }

    if ((cursor = parse_digit(cursor, &x2)) != 0) {
        triangle->x2[j] = x2;
    } else {
        return 0;
    }

    if ((cursor = parse_digit(cursor, &y2)) != 0) {
        triangle->y2[j] = y2;
    } else {
        return 0;
    }

    if ((cursor = parse_comma(cursor)) == 0) {
        return 0;
    }

    if ((cursor = parse_digit(cursor, &x3)) != 0) {
        triangle->x3[j] = x3;
    } else {
        return 0;
    }

    if ((cursor = parse_digit(cursor, &y3)) != 0) {
        triangle->y3[j] = y3;
    } else {
        return 0;
    }

    if ((cursor = parse_comma(cursor)) == 0) {
        return 0;
    }

    if ((cursor = parse_digit(cursor, &x4)) != 0) {
        triangle->x4[j] = x4;
    } else {
        return 0;
    }

    if ((cursor = parse_digit(cursor, &y4)) != 0) {
        triangle->y4[j] = y4;
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
