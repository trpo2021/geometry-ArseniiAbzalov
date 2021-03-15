#pragma once
#define SIZE_ARR_OBJ 4
#define SIZE_STR 64
//#define M_PI 3.14159265358979323846

struct figure_circle {
    double x;
    double y;
    double radius;
};

struct figure_triangle {
    double x1;
    double y1;
    double x2;
    double y2;
    double x3;
    double y3;
    double x4;
    double y4;
};

double calc_square_circle(struct figure_circle* circle, int k);
double calc_perimeter_circle(struct figure_circle* circle, int k);
double calc_perimeter_triangle(struct figure_triangle* triangle, int h);
double calc_square_triangle(struct figure_triangle* triangle, int h);
char* parse_circle(char* cursor,int i, struct figure_circle* circle);
char* parse_triangle(char* cursor, int j, struct figure_triangle* triangle);
