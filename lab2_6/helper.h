

#ifndef LAB2_6_HELPER_H
#define LAB2_6_HELPER_H

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

typedef long long ll;

typedef enum flag_status_code{
    Ro,
    Zr,
    Cv,
    CV,
    not_my,
    u
}flag;

typedef enum not_my_flg{
    INT,
    DOUB,
    LD,
    POINTER,
    CHAR,
    STRING,
    LL,
    LI,
    un
} not_my_flag;

int howmuch(char* str, int count);
not_my_flag another_flag(char* string, int* amount);
flag type_flag(char* string);
void add_to_buffer_1(char** buf, int* size_buf, int* written, int* want, char new);
void add_to_buffer(char** buf, int* size_buf, int* written, int* want, char* new);
bool is_lower_alpha(char c);
bool is_upper_alpha(char c);
int length_long_long(long long number);
ll string_cc_to_10CC_lower(char *string, int base, int* amount);
ll string_cc_to_10CC_upper(char *string, int base, int* amount);
int roman_to_int(char* str);
unsigned int* fib_row(unsigned int max, int *amount);
int zeck_to_int(char* str);
int overfscanf(FILE* stream, char* format, ...);
int oversscanf(char* str, char* format, ...);


#endif //LAB2_6_HELPER_H
