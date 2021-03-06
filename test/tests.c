#include "ctest.h"
#include <libgeometry/functions.h>
#include <math.h>
#include <stdio.h>

CTEST(parse_circle, Error_name)
{
    int num_circle = 1;
    char str[SIZE_STR] = {"ircle  (1 3, 5) "};
    char* startcursor = str;
    char* cursor = str;
    figure_circle circle[num_circle];

    int real = parse_circle(str, startcursor, cursor, circle, num_circle);

    int exp = -1;

    ASSERT_EQUAL(exp, real);
}

CTEST(parse_circle, Error_left_bracket_absence)
{
    int num_circle = 1;
    char str[SIZE_STR] = {"circle 1 3, 5)"};
    char* startcursor = str;
    char* cursor = str;
    figure_circle circle[num_circle];

    int real = parse_circle(str, startcursor, cursor, circle, num_circle);

    int exp = -2;

    ASSERT_EQUAL(exp, real);
}

CTEST(parse_circle, Error_left_bracket_not_correct)
{
    int num_circle = 1;
    char str[SIZE_STR] = {"circle #1 3, 5)"};
    char* startcursor = str;
    char* cursor = str;
    figure_circle circle[num_circle];

    int real = parse_circle(str, startcursor, cursor, circle, num_circle);

    int exp = -2;

    ASSERT_EQUAL(exp, real);
}

CTEST(parse_circle, Error_x_not_correct)
{
    int num_circle = 1;
    char str[SIZE_STR] = {"circle (% 3, 5)"};
    char* startcursor = str;
    char* cursor = str;
    figure_circle circle[num_circle];

    int real = parse_circle(str, startcursor, cursor, circle, num_circle);

    int exp = -3;

    ASSERT_EQUAL(exp, real);
}

CTEST(parse_circle, Error_y_absence)
{
    int num_circle = 1;
    char str[SIZE_STR] = {"circle (1 , 5)"};
    char* startcursor = str;
    char* cursor = str;
    figure_circle circle[num_circle];

    int real = parse_circle(str, startcursor, cursor, circle, num_circle);

    int exp = -4;

    ASSERT_EQUAL(exp, real);
}

CTEST(parse_circle, Error_y_not_correct)
{
    int num_circle = 1;
    char str[SIZE_STR] = {"circle (1 %, 5)"};
    char* startcursor = str;
    char* cursor = str;
    figure_circle circle[num_circle];

    int real = parse_circle(str, startcursor, cursor, circle, num_circle);

    int exp = -4;

    ASSERT_EQUAL(exp, real);
}

CTEST(parse_circle, Error_comma_absence)
{
    int num_circle = 1;
    char str[SIZE_STR] = {"circle (1 3 5)"};
    char* startcursor = str;
    char* cursor = str;
    figure_circle circle[num_circle];

    int real = parse_circle(str, startcursor, cursor, circle, num_circle);

    int exp = -5;

    ASSERT_EQUAL(exp, real);
}

CTEST(parse_circle, Error_comma_not_correct)
{
    int num_circle = 1;
    char str[SIZE_STR] = {"circle (1 3@ 5)"};
    char* startcursor = str;
    char* cursor = str;
    figure_circle circle[num_circle];

    int real = parse_circle(str, startcursor, cursor, circle, num_circle);

    int exp = -5;

    ASSERT_EQUAL(exp, real);
}

CTEST(parse_circle, Error_radius_absence)
{
    int num_circle = 1;
    char str[SIZE_STR] = {"circle (0 0, )"};
    char* startcursor = str;
    char* cursor = str;
    figure_circle circle[num_circle];

    int real = parse_circle(str, startcursor, cursor, circle, num_circle);

    int exp = -6;

    ASSERT_EQUAL(exp, real);
}

CTEST(parse_circle, Error_radius_not_correct)
{
    int num_circle = 1;
    char str[SIZE_STR] = {"circle (0 0, *)"};
    char* startcursor = str;
    char* cursor = str;
    figure_circle circle[num_circle];

    int real = parse_circle(str, startcursor, cursor, circle, num_circle);

    int exp = -6;

    ASSERT_EQUAL(exp, real);
}

CTEST(parse_circle, Error_radius_negative)
{
    int num_circle = 1;
    char str[SIZE_STR] = {"circle (0 0, -3)"};
    char* startcursor = str;
    char* cursor = str;
    figure_circle circle[num_circle];

    int real = parse_circle(str, startcursor, cursor, circle, num_circle);

    int exp = -7;

    ASSERT_EQUAL(exp, real);
}

CTEST(parse_circle, Error_right_bracket_absence)
{
    int num_circle = 1;
    char str[SIZE_STR] = {"circle (1 3, 5 "};
    char* startcursor = str;
    char* cursor = str;
    figure_circle circle[num_circle];

    int real = parse_circle(str, startcursor, cursor, circle, num_circle);

    int exp = -8;

    ASSERT_EQUAL(exp, real);
}

CTEST(parse_circle, Error_right_bracket_not_correct)
{
    int num_circle = 1;
    char str[SIZE_STR] = {"circle (1 3, 5$"};
    char* startcursor = str;
    char* cursor = str;
    figure_circle circle[num_circle];

    int real = parse_circle(str, startcursor, cursor, circle, num_circle);

    int exp = -8;

    ASSERT_EQUAL(exp, real);
}

CTEST(parse_circle, Error_eof)
{
    int num_circle = 1;
    char str[SIZE_STR] = {"circle(0   0 , 3)  x"};
    char* startcursor = str;
    char* cursor = str;
    figure_circle circle[num_circle];

    int real = parse_circle(str, startcursor, cursor, circle, num_circle);

    int exp = -9;

    ASSERT_EQUAL(exp, real);
}

CTEST(cals_circle, Perimeter)
{
    figure_circle circle;
    circle.radius = 3;

    double real = calc_perimeter_circle(circle);

    double exp = 18.84956;

    ASSERT_DBL_NEAR(exp, real);
}

CTEST(cals_circle, Area)
{
    figure_circle circle;
    circle.radius = 3;

    double real = calc_area_circle(circle);

    double exp = 28.27433;

    ASSERT_DBL_NEAR(exp, real);
}

CTEST(cals_circles, Side_length)
{
    double x1, y1, x2, y2;
    x1 = 0;
    y1 = 0;
    x2 = 1;
    y2 = 2;
    double real = fabs(side_length(x2, x1, y2, y1));

    double exp = 2.236;

    ASSERT_DBL_NEAR(exp, real);
}

CTEST(collision, Circle_collision)
{
    int num_circle = 2;
    figure_circle circle[num_circle];
    circle[0].x = 0;
    circle[0].y = 0;
    circle[0].radius = 1;
    circle[1].x = 1;
    circle[1].y = 1;
    circle[1].radius = 1;

    int real = collision(circle[0], circle[1], num_circle);

    int exp = 1;

    ASSERT_EQUAL(exp, real);
}

CTEST(collision, Circle_not_collision)
{
    int num_circle = 2;
    figure_circle circle[num_circle];
    circle[0].x = 0;
    circle[0].y = 0;
    circle[0].radius = 1;
    circle[1].x = 3;
    circle[1].y = 3;
    circle[1].radius = 1;

    int real = collision(circle[0], circle[1], num_circle);

    int exp = 0;

    ASSERT_EQUAL(exp, real);
}
