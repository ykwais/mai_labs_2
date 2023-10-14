#include "enums.h"
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define _INF 1e-20

bool is_number(char *str) {
    char *result;
    long double number = strtold(str, &result);
    if (*result != '\0') {
        return false;
    }
    return true;
}

enum input_status_code analysis(int argc, char **argv) {
    if (argc != 3) {
        return isc_bad_input;
    } else if (!is_number(argv[1])) {
        return isc_not_a_number_eps;
    } else if (!is_number(argv[2])) {
        return isc_not_a_number_x;
    } else if (strtold(argv[1], NULL) < _INF) {
        return isc_little_eps;
    } else if (strtold(argv[1], NULL) > 1.0L) {
        return isc_large_eps;
    } else if ((fabsl(strtold(argv[2], NULL)) - 1.0L) >= 0.0L) {
        return isc_large_x;
    } else {
        return isc_well_x;
    }
}

long double first_summ(long double eps, long double x) {
    long double previous_drob = 1.0L;
    long double next_drob = x;
    long long n = 2;
    long double result = 1.0L + x;
    do {
        if (fabsl(x - n) < eps) {
            result += next_drob;
            next_drob = (previous_drob * x * x) / ((n - 1) * n);
            n++;
            continue;
        }
        previous_drob = next_drob;
        next_drob = (previous_drob * x) / n;
        result += next_drob;
        n++;



    } while (fabsl(next_drob - previous_drob) > eps);
    return result;
}

long double second_summ(long double eps, long double x) {

    long long n = 0;
    long double answer = 1.0L;
    long double previous_drob = 0.0L;
    long double next_drob = 1.0L;

    while (fabsl(next_drob - previous_drob) > eps) {
        previous_drob = next_drob;
        next_drob = (previous_drob * ((-1.0L) * x * x)) / (4 * n * n + 6 * n + 2);
        answer += next_drob;
        n++;
    }
    return answer;
}

long double third_summ(long double eps, long double x) {
    long long n = 0;
    long double answer = 1.0L;
    long double previous_drob = 0.0L;
    long double next_drob = 1.0L;
    while (fabsl(next_drob - previous_drob) > eps) {
        previous_drob = next_drob;
        next_drob = previous_drob * (9 * n * n * x * x + 18 * n * x * x + 9 * x * x) / (9 * n * n + 9 * n + 2);
        answer += next_drob;
        n++;
    }
    return answer;
}


long double fourth_summ(long double eps, long double x) {

    long long n = 1;
    long double answer = 0.0L;
    long double previous_drob = 0.0L;
    long double next_drob = 1.0L;
    while (fabsl(next_drob - previous_drob) > eps) {
        previous_drob = next_drob;
        next_drob = previous_drob * (-1.0L*x * x * (2*n -1 ) / (2*n));
        answer += next_drob;
        n++;
    }
    return answer;
}




