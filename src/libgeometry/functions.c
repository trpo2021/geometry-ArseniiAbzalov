#include "libgeometry/functions.h"
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_ARR_OBJ 4

double side_length(double x1, double y1, double x2, double y2)
{
    return sqrt((pow((y1 - x1), 2)) + (pow((y2 - x2), 2)));
}

bool collision(figure_circle circle_i, figure_circle circle_j, int num_circle)
{
    double length_between_points, sum_of_radius;

    for (int i = 0; i < num_circle; i++) {
        for (int j = 0; j < num_circle; j++) {
            if (i != j) {
                sum_of_radius = fabs((circle_i.radius + circle_j.radius));
                length_between_points = side_length(
                        circle_j.x, circle_i.x, circle_j.y, circle_i.y);
                if (length_between_points <= sum_of_radius)
                    return true;
            }
        }
    }
    return false;
}

double calc_perimeter_circle(figure_circle circle)
{
    return 2 * M_PI * circle.radius;
}

double calc_area_circle(figure_circle circle)
{
    return M_PI * pow(circle.radius, 2);
}

static char* parse_bracket(char* cursor, char sign)
{
    while (*cursor != sign) {
        if (*cursor == ' ')
            cursor++;
        else
            return NULL;
    }
    if (*cursor == sign) {
        cursor++;
        return cursor;
    }
    return cursor;
}

static char* parse_digit(char* cursor, double* num)
{
    char* end;
    while (isdigit(*cursor) == 0) {
        if (*cursor == '-') {
            *num = strtod(cursor, &end);
            cursor = end;
            return cursor;
        } else {
            if (*cursor == ' ') {
                cursor++;
            } else {
                return NULL;
            }
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
        if (*cursor == ' ')
            cursor++;
        else
            return NULL;
    }
    if (*cursor == ',') {
        cursor++;
        return cursor;
    }
    return cursor;
}

static char* check_eof(char* cursor)
{
    while (*cursor != '\n') {
        if (*cursor != ' ') {
            return NULL;
        }
        cursor++;
    }
    return cursor;
}

int parse_circle(
        char str[],
        char* startcursor,
        char* cursor,
        figure_circle* circle,
        int num_circle)
{
    startcursor = str;
    cursor = str;
    char Circle[] = {"circle"};

    while (*startcursor == ' ') {
        startcursor++;
        cursor++;
    }
    if (isalpha(*startcursor) != 0) {
        while (isalpha(*cursor) != 0) {
            cursor++;
        }
    }
    if (strncasecmp(startcursor, "circle", strlen(Circle)) != 0)
        return -1;

    double digit;

    if ((cursor = parse_bracket(cursor, '(')) == NULL) {
        return -2;
    }
    if ((cursor = parse_digit(cursor, &digit)) == NULL) {
        return -3;
    } else {
        circle[num_circle].x = digit;
    }

    if ((cursor = parse_digit(cursor, &digit)) == NULL) {
        return -4;
    } else {
        circle[num_circle].y = digit;
    }

    if ((cursor = parse_comma(cursor)) == NULL) {
        return -5;
    }

    if ((cursor = parse_digit(cursor, &digit)) == NULL) {
        return -6;
    } else {
        if (digit <= 0)
            return -7;
        else
            circle[num_circle].radius = digit;
    }

    if ((cursor = parse_bracket(cursor, ')')) == NULL) {
        return -8;
    }

    if ((cursor = check_eof(cursor)) == NULL) {
        return -9;
    }
    return 0;
}
