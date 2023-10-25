
#ifndef LAB2_10_HELPER_H
#define LAB2_10_HELPER_H

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

typedef long double ld;

typedef long long ll;

typedef enum transformations_status_code{
    tsc_mem_problem,
    tsc_invalid_n,
    tsc_well
}checker;

ld get_value_polynom(ld value, ld** array_coef, int count);
void copy(ld** first, ld** second, int count);
void get_diff_coeffs(ld** input, int count);
ld get_g_coeffs(ld a, ld** input, int count);
checker collect_new_coeffs(ld a, ld** input, ld** result, int n, ... );
void print_coeffs(ld** input, ld** result, int count);


#endif //LAB2_10_HELPER_H
