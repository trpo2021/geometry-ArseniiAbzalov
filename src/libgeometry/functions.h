#pragma once
#define SIZE_ARR_OBJ 4
#define SIZE_STR 64

typedef struct {
    double x;
    double y;
    double radius;
    double perimeter;
    double area;
} figure_circle;

double side_length(double x1, double y1, double x2, double y2);

double calc_area_circle(figure_circle circle);
double calc_perimeter_circle(figure_circle circle);
void collision(
        figure_circle* circle,
        int num_circle,
        int collisions[num_circle][num_circle]);
int parse_circle(
        char str[],
        char* startcursor,
        char* cursor,
        figure_circle* circle,
        int num_circle);
