

#ifndef LAB2_9_HELPER_H
#define LAB2_9_HELPER_H
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

enum mem_status_code{
    msc_well,
    msc_problem
};

typedef enum mem_status_code memory;

void sim(int num);
int* simple_mult(long long number, int* length,memory* stata);
long long gcd(long long a, long long b);
long long get_denominator(double number);
void comparison_array_int(int* main, int size1, int* supp, int size2, int pos);
void final_representation(long long base, int count, ...);

#endif //LAB2_9_HELPER_H
