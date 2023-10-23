#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct{
    char* filename;
    int strok_number;
    int symbol_number;

}one_file;

void left_shift(char** mass, int len)
{
    for(int i = 0; i < len -1; ++i)
    {
        (*mass)[i] = (*mass)[i+1];
    }
}

bool is_same(char* pattern, char* array, int len)
{
    for(int i = 0; i < len; i++){
        if(pattern[i] != array[i]){
            return false;
        }
    }
    return true;
}

void find_pattern_in_file(one_file** result,char* pattern, char* filename, int* count_matches){

    one_file* tmp = NULL;
    int length_of_pattern = strlen(pattern);

    if(length_of_pattern == 0){
        return;//подойдет все-что угодно
    }

    int count_slash_n = 0;

    for(int i = 0; i < length_of_pattern; ++i){
        if(pattern[i] == '\n'){
            count_slash_n++;
        }

    }
    int saved_clash_n = count_slash_n;

    char* array_symbols = (char*)malloc(sizeof(char)*length_of_pattern);
    if(array_symbols == NULL){
        return;//enum
    }
    array_symbols[length_of_pattern] = '\0';
    int counter_string = 1;
    int counter_symb = 1;

    FILE* file = NULL;
    if(!(file = fopen(filename, "r"))){
        return;//file troubles
    }

    int saved_pos_num = 0;
    char one_byte = 0;
    int i = 0;

    while(fread(&one_byte, sizeof(char), sizeof(one_byte), file)){
        if(i == length_of_pattern){
            left_shift(&array_symbols, length_of_pattern);
            i--;
        }

        counter_symb++;

        saved_pos_num = counter_symb;

        if(one_byte == '\n' && !saved_clash_n){///////////////////////////
//            if(count_slash_n > 0){
//                saved_pos_num = counter_symb;
//            }else{
//                saved_pos_num = counter_symb;//////////////////////////
//            }
            //saved_clash_n = count_slash_n;
            counter_string++;
            counter_symb = 1;
            //saved_pos_num = counter_symb;
        }

        if(one_byte == '\n' && saved_clash_n){
            counter_string++;
            saved_clash_n--;
            counter_symb = saved_pos_num;
        }
        array_symbols[i] = one_byte;

        if(is_same(pattern, array_symbols, length_of_pattern)){

            int qolvo = *count_matches;
            if( !(tmp = (one_file*)realloc(*result, sizeof(one_file)*(qolvo+1)))){
                //enum
                free(result);
                return;
            }else{
                *result = tmp;
            }

            (*result)[qolvo].filename = filename;
            (*result)[qolvo].strok_number = counter_string - count_slash_n;
            (*result)[qolvo].symbol_number = counter_symb-length_of_pattern;
            (*count_matches)++;
            saved_clash_n = count_slash_n;
        }

        i++;
    }
    free(array_symbols);
    fclose(file);
}

void pattern_search(one_file** result,char* pattern,int* count_matches, int count, ...){

    va_list ptr;
    va_start(ptr, count);
    for(int i = 0; i < count; ++i){

        char* name = va_arg(ptr, char*);

        find_pattern_in_file(result,pattern, name, count_matches);

    }

    va_end(ptr);
}



int main() {
    int count_of_file = 2;
    int count_matches = 0;
    one_file* result_info = (one_file*) malloc(sizeof(one_file));
    if(result_info == NULL){
        printf("no mem\n");
        return 0;
    }
    pattern_search(&result_info, "ab\nc",&count_matches, count_of_file, "file1.txt","file2.txt");

    for(int i = 0; i < count_matches; ++i){
        printf("%s\n", result_info[i].filename);
        printf("number string: %d\n", result_info[i].strok_number);
        printf("number symbol: %d\n", result_info[i].symbol_number);
    }

    

    free(result_info);
}
