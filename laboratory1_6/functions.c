#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "enums.h"

#define _INF 1e-7

bool is_number(char *str) {
    char *result;
    long double number = strtold(str, &result);
    if (*result != '\0') {
        return false;
    }
    return true;
}

enum input_status_code analysis(int argc, char **argv) {
    if (argc != 2) {
        return isc_bad_input;
    } else if (!is_number(argv[1])) {
        return isc_not_a_number_eps;
    } else if (strtold(argv[1], NULL) < _INF) {
        return isc_little_eps;
    } else if (strtold(argv[1], NULL) > 1.0L) {
        return isc_large_eps;
    } else {
        return isc_well;
    }
}

long double first_function(long double eps, long double x) {
    if (x == 0.0L) {
        return logl(1.0L + x) / (x + eps);
    }
    return logl(1.0L + x) / x;
}

long double second_function(long double eps, long double x) {
    if (x < eps) {
        x = 1.0L;
    }
    return expl(-x * x * 0.5L);
}

long double third_function(long double eps, long double x) {
    if (x == 1.0L) {
        return logl(1.0L / (1.0L - x + eps));
    }
    return logl(1.0L / (1.0L - x));
}


long double fourth_function(long double eps, long double x) {
    if (x < eps) {
        return powl(x + eps, x + eps);
    }
    return powl(x, x);
}

long double the_parabola_method(long double eps, long double bottom, long double top,
                                long double(*function)(long double, long double)) {
    int n = 2;
    long double previous_result = 0.0L;
    long double next_result = 0.0L;
    long double step = 0.0L;
    long double odd_numbers = 0.0L;
    long double even_numbers = 0.0L;
    long double x_0 = 0.0L;
    do {

        step = (top - bottom) / n;
        previous_result = next_result;

        next_result = function(eps, bottom);
        next_result += function(eps, top);

        for (int i = 1; i < n; i += 2) {
            x_0 = bottom + i * step;
            odd_numbers += function(eps, x_0);

        }

        for (int i = 2; i < n - 1; i += 2) {
            x_0 = bottom + i * step;
            even_numbers += function(eps, x_0);

        }

        next_result += 4.0L * odd_numbers;
        next_result += 2.0L * even_numbers;

        next_result *= (step / 3.0L);

        odd_numbers = 0.0L;
        even_numbers = 0.0L;

        n *= 2;

    } while (fabsl(next_result - previous_result) > eps);

    return next_result;
}














