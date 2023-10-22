

#ifndef LAB2_1_HELPER_H
#define LAB2_1_HELPER_H
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

typedef enum input_status_code{
    isc_bad_input,
    isc_l,
    isc_r,
    isc_u,
    isc_n,
    isc_c
}input;

typedef enum ui_status_code{
    usc_well,
    usc_overflow,
    usc_bad_number
}uint;

int my_strlen(const char* string);
int my_strcmp(const char* first, const char* second);
input analysis(int argc, char** argv);
char* reverse_string(char* str);
char* up_half_string(char* str);
char* ordered_string(char* str);
uint arg_to_ud(char* str, unsigned int* answer);
int random_number(int min, int max);
void string_permutations(char** strs, int size);
char* concatenation(char** strs, int count);

#endif //LAB2_1_HELPER_H
