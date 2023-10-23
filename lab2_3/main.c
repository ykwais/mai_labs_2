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



    char* array_symbols = (char*)malloc(sizeof(char)*length_of_pattern);
    if(array_symbols == NULL){
        return;//enum
    }
    array_symbols[length_of_pattern] = '\0';
    int counter_string = 1;
    int counter_symb = 1;


    FILE* file = NULL;
    if(!(file = fopen(filename, "r+"))){
        return;//file troubles
    }


    int one_byte = 0;
    int position = 0;

    if(fseek(file,  0,SEEK_SET)!=0){
        printf("troublefffffffffffffff");
        return;//enum
    }


    //printf("start pos: %d\n", ftell(file));
    while((one_byte = fgetc(file)) != EOF){
        //printf("beg pos: %d\n", ftell(file));
        position++;
        int colvo = 0;

        if(one_byte == pattern[0]){
            array_symbols[0] = one_byte;
            for(int i = 1; i < length_of_pattern;++i ){
                int two_byte = 0;
                if((two_byte = fgetc(file))!=EOF){
                    //printf("beg pos: %d\n", ftell(file));
                    position++;
                    array_symbols[i] = two_byte;
                    colvo++;
                }
            }
            int sdvig = -1*colvo;
            position = position - colvo ;
            //printf("prev pos: %d\n", ftell(file));
            if(fseek(file,  position,SEEK_SET)!=0){
                printf("trouble");
                return;//enum
            }
            //printf("next pos: %d\n", ftell(file));

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
                (*result)[qolvo].strok_number = counter_string;

                (*result)[qolvo].symbol_number = counter_symb;

                (*count_matches)++;
                for(int i = 0; i < length_of_pattern; ++i){
                    array_symbols[i] = 0;
                }
                //continue;
            }
            //continue;

        }
        if(one_byte == '\n'){
            counter_string++;
            counter_symb = 1;
        }else{
            counter_symb++;
        }
        for(int i = 0; i < length_of_pattern; ++i){
            array_symbols[i] = 0;
        }

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
   pattern_search(&result_info, "\n\n\n\n",&count_matches, count_of_file, "file1.txt","file2.txt");

    for(int i = 0; i < count_matches; ++i){
        printf("%s\n", result_info[i].filename);
        printf("number string: %d\n", result_info[i].strok_number);
        printf("number symbol: %d\n", result_info[i].symbol_number);
    }

    free(result_info);
}
