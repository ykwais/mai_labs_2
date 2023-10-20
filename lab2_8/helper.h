

#ifndef LAB2_8_HELPER_H
#define LAB2_8_HELPER_H

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <ctype.h>


enum mem_status_code{
    msc_well,
    msc_problem
};

typedef enum mem_status_code memory;



char* delete_zeros(char* str);
char* add_base(memory* stata, int base, char* first, char* second);
char* adding(memory* stata, int base, int count, ...);


#endif //LAB2_8_HELPER_H
