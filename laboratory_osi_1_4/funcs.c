#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "enums.h"

input analysis(int argc, char **argv) {
    if (argc > 4 || argc < 3) {
        return isc_too_args;
    }
    if (!strcmp(argv[1], "xor8") && argc == 3) {
        return isc_xor8;
    }
    if (!strcmp(argv[1], "xor32") && argc == 3) {
        return isc_xor32;
    }
    if (!strcmp(argv[1], "mask") && argc == 4) {
        return isc_mask;
    }

    return isc_bad_input;
}

void xor_8(char *name_file, int *answer, file_troubles *status) {
    FILE *input_file = NULL;
    *status = ofp_well;

    if (!(input_file = fopen(name_file, "r"))) {
        *status = ofp_bad_open;
        return;
    }

    char one_byte = 0;

    while (fread(&one_byte, sizeof(char), sizeof(one_byte), input_file)) {
        *answer ^= one_byte;
    }

    fclose(input_file);


}


void xor_32(char *name_file, char *answer, file_troubles *status) {
    FILE *input_file = NULL;
    *status = ofp_well;

    if (!(input_file = fopen(name_file, "r"))) {
        *status = ofp_bad_open;
        return;
    }

    char buffer[4];
    size_t count_read = 0;

    while ((count_read = fread(buffer, sizeof(char), sizeof(buffer), input_file))) {
        if (4 != count_read) {
            for (size_t i = count_read; i < 4; ++i) {
                buffer[i] = 0;
            }
        }
        for (int i = 0; i < 4; ++i) {
            answer[i] = answer[i]^buffer[i];
        }
    }

    fclose(input_file);

}

bool valid_symbols(char symbol){
    return ((symbol >= 'A' && symbol < 'G') || (symbol >= '0' && symbol <= '9') );
}

char* get_mask(char* argv, memory* status_memory, valid_mask* status_mask){
    *status_memory = mt_well;
    *status_mask = vvm_valid;
    int counter = 0;
    char* mask = malloc(sizeof(char)* 4);
    if(mask == NULL){
        *status_memory = mt_memory_problem;
        return NULL;
    }
    int length = strlen(argv);
    if(length < 4)
    {
        for(int i = 0; i < 4; i++)
        {
            mask[i] = 0;
        }
    }
    for(int i = 0; i < length && counter < 4; ++i)
    {
        char symb = (char)toupper(argv[i]);
        if(valid_symbols(symb))
        {
            mask[counter] = (symb > '9') ?  (char)(symb - 'A' + 10) :  (char)(symb - '0');
        }
        else{
            *status_mask = vvm_invalid;
            mask[counter] = 0;
        }

        counter++;
    }

    return mask;

}

void mask_func(char *file_name, int *counter, char *mask, file_troubles *status) {
    FILE *input_file = NULL;
    *status = ofp_well;
    if (!(input_file = fopen(file_name, "r"))) {
        *status = ofp_bad_open;
        return;
    }

    char buffer_4[4];

    int local_counter = 0;

    size_t count_readed = 0;
    while ((count_readed = fread(buffer_4, sizeof(char), sizeof(buffer_4), input_file))) {
        if (count_readed < 4) {
            for (size_t i = count_readed; i < 4; ++i) {
                buffer_4[i] = 0;
            }
        }
        for(int i = 0; i < 4; ++i){

            if((buffer_4[i] & mask[i]) == mask[i])
            {
                local_counter++;
            }
        }
        if(local_counter == 4)
        {
            printf("\n");
            for(int i = 0; i < 4; ++i){
                printf("%c", buffer_4[i]);
            }
            printf("\n");
            (*counter)++;
        }
        local_counter = 0;



    }

    fclose(input_file);
}
