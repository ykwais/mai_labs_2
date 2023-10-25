
#ifndef LAB2_4_HELPER_H
#define LAB2_4_HELPER_H

#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <math.h>

typedef long double ld;

typedef struct{
    ld x;
    ld y;
} point;

bool is_zero(ld eps, point f, point s);
bool check(ld eps, point* first, point* second, ld* curr, ld* prev);
bool is_convex(ld eps, int count, ...);
ld polynom(double value, int n, ...);

#endif //LAB2_4_HELPER_H
