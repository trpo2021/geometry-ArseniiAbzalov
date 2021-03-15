#include "libgeometry/functions.h"
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_ARR_OBJ 4

static bool check_correct_triangle(struct figure_triangle* triangle, int j)
{
    if ((triangle[j].x1 != triangle[j].x4)
        || (triangle[j].y1 != triangle[j].y4)) {
        printf("uncorrect triangle\n");
        return false;
    }
    return true;
}

static double side_length(double x1, double y1, double x2, double y2)
{
    return sqrt((pow((y1 - x1), 2)) + (pow((y2 - x2), 2)));
}
double calc_perimeter_circle(struct figure_circle* circle, int k)
{
    return 2 * M_PI * circle[k].radius;
}

double calc_square_circle(struct figure_circle* circle, int k)
{
    return M_PI * pow(circle[k].radius, 2);
}

double calc_perimeter_triangle(struct figure_triangle* triangle, int h)
{
    double a, b, c;

    a = side_length(
            triangle[h].x1, triangle[h].x2, triangle[h].y1, triangle[h].y2);
    b = side_length(
            triangle[h].x2, triangle[h].x3, triangle[h].y2, triangle[h].y3);
    c = side_length(
            triangle[h].x3, triangle[h].x1, triangle[h].y3, triangle[h].y1);

    return a + b + c;
}

double calc_square_triangle(struct figure_triangle* triangle, int h)
{
    double a, b, c, p;

    a = side_length(
            triangle[h].x1, triangle[h].x2, triangle[h].y1, triangle[h].y2);
    b = side_length(
            triangle[h].x2, triangle[h].x3, triangle[h].y2, triangle[h].y3);
    c = side_length(
            triangle[h].x3, triangle[h].x1, triangle[h].y3, triangle[h].y1);

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
        circle[i].x = x1;
    } else {
        return 0;
    }

    if ((cursor = parse_digit(cursor, &y1)) != 0) {
        circle[i].y = y1;
    } else {
        return 0;
    }

    if ((cursor = parse_comma(cursor)) == 0) {
        return 0;
    }

    if ((cursor = parse_digit(cursor, &radius1)) != 0) {
        circle[i].radius = radius1;
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
        triangle[j].x1 = x1;
    } else {
        return 0;
    }

    if ((cursor = parse_digit(cursor, &y1)) != 0) {
        triangle[j].y1 = y1;
    } else {
        return 0;
    }

    if ((cursor = parse_comma(cursor)) == 0) {
        return 0;
    }

    if ((cursor = parse_digit(cursor, &x2)) != 0) {
        triangle[j].x2 = x2;
    } else {
        return 0;
    }

    if ((cursor = parse_digit(cursor, &y2)) != 0) {
        triangle[j].y2 = y2;
    } else {
        return 0;
    }

    if ((cursor = parse_comma(cursor)) == 0) {
        return 0;
    }

    if ((cursor = parse_digit(cursor, &x3)) != 0) {
        triangle[j].x3 = x3;
    } else {
        return 0;
    }

    if ((cursor = parse_digit(cursor, &y3)) != 0) {
        triangle[j].y3 = y3;
    } else {
        return 0;
    }

    if ((cursor = parse_comma(cursor)) == 0) {
        return 0;
    }

    if ((cursor = parse_digit(cursor, &x4)) != 0) {
        triangle[j].x4 = x4;
    } else {
        return 0;
    }

    if ((cursor = parse_digit(cursor, &y4)) != 0) {
        triangle[j].y4 = y4;
    } else {
        return 0;
    }

    if ((check_correct_triangle(triangle, j)) == 0) {
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
