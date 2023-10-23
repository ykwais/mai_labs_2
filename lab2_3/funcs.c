#include "helper.h"

status find_pattern_in_file(one_file** result,char* pattern, char* filename, int* count_matches){

    one_file* tmp = NULL;
    int length_of_pattern = strlen(pattern);


    if(length_of_pattern == 0){
        return null_pattern;//подойдет все-что угодно
    }

    int counter_string = 1;
    int counter_symb = 1;


    FILE* file = NULL;
    if(!(file = fopen(filename, "r+"))){
        return file_problem;//file troubles
    }


    int one_byte = 0;
    int position = 0;

    if(fseek(file,  0,SEEK_SET)!=0){
        return fseek_problem;//enum
    }



    while((one_byte = fgetc(file)) != EOF){

        position++;
        int colvo = 0;

        if(one_byte == pattern[0]){

            for(int i = 1; i < length_of_pattern;++i ){
                int two_byte = 0;
                if((two_byte = fgetc(file))!=EOF){
                    if(two_byte == pattern[i]){
                        position++;
                        colvo++;
                    }


                }
            }
            if(colvo == length_of_pattern-1){
                int qolvo = *count_matches;
                if( !(tmp = (one_file*)realloc(*result, sizeof(one_file)*(qolvo+1)))){

                    free(result);
                    return mem_problem;
                }else{
                    *result = tmp;
                }

                (*result)[qolvo].filename = filename;
                (*result)[qolvo].strok_number = counter_string;

                (*result)[qolvo].symbol_number = counter_symb;

                (*count_matches)++;
            }


            position = position - colvo ;

            if(fseek(file,  position,SEEK_SET)!=0){
                return fseek_problem;//enum
            }



        }
        if(one_byte == '\n'){
            counter_string++;
            counter_symb = 1;
        }else{
            counter_symb++;
        }


    }

    fclose(file);
    return all_well;
}



status pattern_search(one_file** result,char* pattern,int* count_matches, int count, ...){
    status stat;
    va_list ptr;
    va_start(ptr, count);
    for(int i = 0; i < count; ++i){

        char* name = va_arg(ptr, char*);

        stat = find_pattern_in_file(result,pattern, name, count_matches);
        if(stat != all_well){
            return stat;
        }

    }

    va_end(ptr);
    return all_well;
}
