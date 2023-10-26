
#ifndef LAB2_5_HELPER_H
#define LAB2_5_HELPER_H


#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <stdbool.h>

typedef long long ll;

typedef enum flag_status_code{
    Ro,
    Zr,
    Cv,
    CV,
    to,
    TO,
    mi,
    mu,
    md,
    mf,
    not_my,
    u
}flag;


int overfprintf(FILE* stream, char* format, ...);
flag type_flag(char* string);
void add_to_buffer_1(char** buf, int* size_buf, int* written, int* want, char new);
void add_to_buffer(char** buf, int* size_buf, int* written, int* want, char* new);
char* int_to_rom(int num, int* amount );
char* zeck(unsigned int number, int* amount);
unsigned int* fib_row(unsigned int max, int *amount);
char* cc10_to_base_cc_lower(int num, int base, int* amount);
char* cc10_to_base_cc_upper(ll num, int base, int* amount);
bool is_lower_alpha(char c);
bool is_upper_alpha(char c);
int length_long_long(long long number);
char* string_cc_to_10CC_lower(char *string, int base, int* amount);
char* string_cc_to_10CC_upper(char *string, int base, int* amount);
char* dump(const void *value, int size_of, int* amount);



#endif //LAB2_5_HELPER_H
