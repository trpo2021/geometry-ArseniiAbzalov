#include "libgeometry/functions.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main()
{
    struct figure_circle circle;
    struct figure_triangle triangle;

    char str[SIZE_STR];
    char* startcursor = str;
    char* cursor = str;
    int i = 0, j = 0;

    while (fgets(str, SIZE_STR, stdin)) {
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
            if (parse_circle(cursor, i, &circle) != 0) {
                i++;
            }
        } else {
            if (strncasecmp(startcursor, "triangle", cursor - startcursor)
                == 0) {
                if (parse_triangle(cursor, j, &triangle) != 0) {
                    j++;
                }
            } else {
                printf("^\n");
                printf("Error at column 0: expected 'circle' or 'triangle'\n");
            }
        }
    }
    printf("\n");

    for (int k = 0; k < i; k++) {
        printf("circle (%.1f %.1f, %.1f)\n",
               circle.x[k],
               circle.y[k],
               circle.radius[k]);
        printf("perimeter = %.1f\n", calc_perimeter_circle(&circle, k));
        printf("square = %.1f\n\n", calc_square_circle(&circle, k));
    }
    for (int h = 0; h < j; h++) {
        printf("triangle ((%.1f %.1f, %.1f %.1f, %.1f %.1f, %.1f %.1f))\n",
               triangle.x1[h],
               triangle.y1[h],
               triangle.x2[h],
               triangle.y2[h],
               triangle.x3[h],
               triangle.y3[h],
               triangle.x4[h],
               triangle.y4[h]);
        if (calc_perimeter_triangle(&triangle, h) != 0) {
            printf("perimeter1 = %.1f\n",
                   calc_perimeter_triangle(&triangle, h));
            printf("square = %.1f\n\n", calc_square_triangle(&triangle, h));
        }
    }

    return 0;
}
