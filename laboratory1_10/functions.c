#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "enums.h"

#define SIZE 65

enum input_status_code_base is_well_base(int *base) {
    if (*base < 2 || *base > 36) {
        return iscb_bad;
    }
    return iscb_well;
}

enum input_status_code_size_of_number analysis_10cc(long long number){
    if(number < 0){
        return iscson_overflow;
    }
    return iscson_well;
}


long long string_cc_to_10CC(int base, char *string, int negative) {
    char *ptr = string + negative;
    long long result = 0;
    while (*ptr) {
        result = result * base + (isdigit(*ptr) ? *ptr - '0' : *ptr - 'A' + 10);
        ptr++;
    }
    if (negative == 1) {
        return -1 * result;
    } else {
        return result;
    }
}

void cc10_to_base_cc(int base, long long number, int* deductible, char mass[]) {
    for(int i = 0; i < SIZE+1; i++){
        mass[i] = '\0';
    }
    long long num = number;
    int r;
    if (num < 0) {
        num *= -1;}
    char buf[SIZE + 1];
    char *ptr = buf + SIZE - 1;
    *ptr = 0;
    ptr--;
    int counter = 0;
    while (num > 0) {
        r = num % base;
        *ptr = (r > 9) ? r - 10 + 'A' : r + 48;
        ptr--;
        num /= base;
        counter++;
    }
    if (number < 0) {
        printf("-");
    }
    *deductible = counter;
    for(int i = 0; i < SIZE+1; i++){
        mass[i] = buf[i];
    }

//    for (int i = SIZE - counter - 1; i < SIZE; i++) {
//        printf("%c", buf[i]);
//    }
//    printf("\n");
}

void print_diff_cc(int schet, char mass[]){
    for (int i = SIZE - schet - 1; i < SIZE; i++) {
        printf("%c", mass[i]);
    }
    printf("\n");
}

void divided_string(char *arg, char *tmp) {

    int length = strlen(arg);
    int counter = 0;

    int p = 0;
    int i = 0;
    if (arg[0] == '-') {
        tmp[0] = '-';
        i++;
        p++;
    }
    while (i < length) {
        if (arg[i] == '0' && !counter) {
            i++;
            continue;
        }
        if (arg[i] != '0') {
            counter++;
            tmp[p] = arg[i];
            p++;
        }
        if (arg[i] == '0' && counter != 0) {
            tmp[p] = arg[i];
            p++;
        }
        i++;
    }
    tmp[p] = '\0';
}

bool acceptable_value_of_cc(int base, char* string){
    char* ptr = string;
    if(base > 9){
        while(*ptr){
            if(*ptr == 45 || (*ptr >= 48 && *ptr <=57) ||  *ptr - 65 + 10 < base){
                ptr++;
            }
            else{
                return false;
            }
        }
    }else{
        while (*ptr){
            if(*ptr == 45 || *ptr - 48 < base){
                ptr++;
            }
            else{
                return false;
            }
        }
    }

    return true;
};