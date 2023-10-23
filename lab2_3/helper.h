

#ifndef LAB2_3_HELPER_H
#define LAB2_3_HELPER_H

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>


typedef struct{
    char* filename;
    int strok_number;
    int symbol_number;
}one_file;

typedef enum function_status_code{
    null_pattern,
    mem_problem,
    file_problem,
    fseek_problem,
    all_well
}status;

status find_pattern_in_file(one_file** result,char* pattern, char* filename, int* count_matches);
status pattern_search(one_file** result,char* pattern,int* count_matches, int count, ...);

#endif //LAB2_3_HELPER_H
