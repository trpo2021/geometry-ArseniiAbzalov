#include "ctest.h"
#include <libgeometry/functions.h>
#include <math.h>
#include <stdio.h>

CTEST(parse_circle, Error_name)
{
    int num_circle = 1;
    char str[SIZE_STR] = {"ircle  (0 3, 5) "};
    char* startcursor = str;
    char* cursor = str;
    figure_circle circle[num_circle];

    int real = parse_circle(str, startcursor, cursor, circle, num_circle);

    int exp = -1;

    ASSERT_EQUAL(exp, real);
}
