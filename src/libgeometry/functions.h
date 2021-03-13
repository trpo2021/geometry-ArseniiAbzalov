#pragma once
#define SIZE_ARR_STRUCT 4
#define SIZE_STR 64
#define PI 3.14

struct figure_circle {
    double x[SIZE_ARR_STRUCT];
    double y[SIZE_ARR_STRUCT];
    double radius[SIZE_ARR_STRUCT];
};

struct figure_triangle {
    double x1[SIZE_ARR_STRUCT];
    double y1[SIZE_ARR_STRUCT];
    double x2[SIZE_ARR_STRUCT];
    double y2[SIZE_ARR_STRUCT];
    double x3[SIZE_ARR_STRUCT];
    double y3[SIZE_ARR_STRUCT];
    double x4[SIZE_ARR_STRUCT];
    double y4[SIZE_ARR_STRUCT];
};

double calc_square_circle(struct figure_circle* circle, int k);
double calc_perimeter_circle(struct figure_circle* circle, int k);
double calc_perimeter_triangle(struct figure_triangle* triangle, int h);
double calc_square_triangle(struct figure_triangle* triangle, int h);
char* parse_circle(char* cursor, int i, struct figure_circle* circle);
char* parse_triangle(char* cursor, int j, struct figure_triangle* triangle);
