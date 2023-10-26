
#ifndef LAB2_5_HELPER_H
#define LAB2_5_HELPER_H


#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

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



#endif //LAB2_5_HELPER_H
