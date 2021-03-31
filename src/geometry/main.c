#include "libgeometry/functions.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main()
{
    figure_circle circle[SIZE_ARR_OBJ];
    char str[SIZE_STR];
    char* startcursor = str;
    char* cursor = str;
    int num_circle = 0;
    int Error = 0;

    while (fgets(str, SIZE_STR, stdin)) {
        Error = parse_circle(str, startcursor, cursor, circle, num_circle);
        if (Error == 0)
            num_circle++;
        else {
            switch (Error) {
            case -1:
                printf("Error at column 0: expected 'circle'\n");
                break;
            case -2:
                printf("expected '('\n");
                break;
            case -3:
                printf("expected 'x' c type 'double'\n");
                break;
            case -4:
                printf("expected 'y' c type 'double'\n");
                break;
            case -5:
                printf("expected ','\n");
                break;
            case -6:
                printf("expected 'radius' c type 'double'\n");
                break;
            case -7:
                printf("uncorrect radius\n");
                break;
            case -8:
                printf("expected ')'\n");
                break;
            case -9:
                printf("unexpected token\n");
                break;
            }
        }
    }
    printf("\n");

    int collisions[num_circle][num_circle];
    collision(circle, num_circle, collisions);

    for (int i = 0; i < num_circle; i++) {
        printf("%d. circle (%.1f %.1f, %.1f)\n",
               i + 1,
               circle[i].x,
               circle[i].y,
               circle[i].radius);
        printf("    perimeter = %.1f\n",
               circle[i].perimeter = calc_perimeter_circle(circle[i]));
        printf("    area = %.1f\n",
               circle[i].area = calc_area_circle(circle[i]));
        printf("    intersects:\n ");

        for (int j = 0; j < num_circle; j++) {
            if (collisions[i][j] == 1) {
                printf("\t %d. circle\n", j + 1);
            }
        }
        printf("\n");
    }

    return 0;
}
