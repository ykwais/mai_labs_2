#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "enums.h"

#define MAX_LEN 255
#define SIZE 33

void skip_the_voids(FILE *file_name) {
    int ch;
    while ((ch = fgetc(file_name)) != EOF) {
        if (ch != ' ' && ch != 9 && ch != 10) {
            ungetc(ch, file_name);
            break;
        }
    }
}

char *collect_a_lexemma(FILE *file_name) {
    char *lexemma = (char *) malloc(sizeof(char) * MAX_LEN);
    if (lexemma == NULL) {
        return NULL;
    }
    int ch;
    int length_lexemma = 0;
    while ((ch = fgetc(file_name)) != EOF) {
        if (ch == 10 || ch == 9 || ch == 32) {
            break;
        }
        if (length_lexemma < MAX_LEN) {
            lexemma[length_lexemma] = (char) ch;
            length_lexemma++;
        } else {
            //статус-код можно добавить
            return NULL;
        }
    }
    lexemma[length_lexemma] = '\0';
    return lexemma;
}

void do_r_flag(FILE *result_file, FILE *file_1, FILE *file_2) {
    bool even = true;
    skip_the_voids(file_1);
    skip_the_voids(file_2);
    while (!feof(file_1) || !feof(file_2)) {
        if (!feof(file_2) && feof(file_1)) {
            even = true;
        }
        if (!feof(file_1) && feof(file_2)) {
            even = false;
        }
        if (even) {
            char *lexemma = collect_a_lexemma(file_2);
            if (lexemma == NULL) {
                fprintf(result_file, "(too_long_string)");
                free(lexemma);
                skip_the_voids(file_2);
                lexemma = NULL;
            } else {
                fprintf(result_file, "%s ", lexemma);
                free(lexemma);
                lexemma = NULL;
                skip_the_voids(file_2);
                even = false;
            }
        } else {
            char *lexemma = collect_a_lexemma(file_1);
            if (lexemma == NULL) {
                fprintf(result_file, "(too_long_string)");
                free(lexemma);
                lexemma = NULL;
                skip_the_voids(file_1);
            } else {
                fprintf(result_file, "%s ", lexemma);
                free(lexemma);
                lexemma = NULL;
                skip_the_voids(file_1);
                even = true;
            }

        }
    }
}

enum flag_r_status_code can_r_flag(char *first_file_name, char *second_file_name, char *third_file_name) {
    FILE *output_file = fopen(third_file_name, "w");
    FILE *input_file_1 = fopen(first_file_name, "r");
    FILE *input_file_2 = fopen(second_file_name, "r");
    if (!output_file || !input_file_1 || !input_file_2) {

        fclose(input_file_1);
        fclose(input_file_2);
        fclose(output_file);
        return r_file_open_problem;
    } else {
        do_r_flag(output_file, input_file_1, input_file_2);
        fclose(input_file_1);
        fclose(input_file_2);
        fclose(output_file);
        output_file = NULL, input_file_1 = NULL, input_file_2 = NULL;
        return r_normal;
    }
}

bool is_LATIN(int x){
    return (x >= 65 && x <= 90);
}

void string_to_4_cc_in_file(char* string, FILE* output_file, int base){
    int length = strlen(string);
    for(int i = 0; i < length; i++){
        if(is_LATIN(string[i])){
            char buf[SIZE];
            char* ptr = buf + SIZE -1;
            int r;
            int num = string[i] + 32;
            *ptr = 0;
            ptr--;
            int counter = 0;
            while(num > 0){
                r = num % base;
                *ptr = (r>9) ? r - 10 + 'A' : r + 48;
                ptr--;
                num /= base;
                counter++;
            }
            for(int i = SIZE - counter-1; i < SIZE-1; i++){
                fprintf(output_file,"%c", buf[i]);
            }
        }else{
            fprintf(output_file, "%c", string[i]);
        }
    }
}

void LATIN_to_latin(char* string, FILE* output_file){
    int length = strlen(string);
    for(int i = 0; i < length; i++){
        if(is_LATIN(string[i])){
            fprintf(output_file, "%c", string[i]+32);
        }else{
            fprintf(output_file, "%c", string[i]);
        }
    }
}

void string_to_8_cc(char* string, FILE* output_file, int base){

    int length = strlen(string);
    for(int i = 0; i < length; i++){

        char buf[SIZE];
        char* ptr = buf + SIZE -1;
        int r;
        int num = string[i];
        *ptr = 0;
        ptr--;
        int counter = 0;
        while(num > 0){
            r = num % base;
            *ptr = (r>9) ? r - 10 + 'A' : r + 48;
            ptr--;
            num /= base;
            counter++;
        }
        for(int i = SIZE - counter-1; i < SIZE-1; i++){
            fprintf(output_file,"%c", buf[i]);
        }

    }
}

void do_a_flag(FILE* input, FILE* output){
    skip_the_voids(input);
    long long counter = 1;
    while(!feof(input)){
        if(counter % 10 == 0){
            char* lexemma = collect_a_lexemma(input);
            if (lexemma == NULL) {
                fprintf(output, "(too_long_string)");
                free(lexemma);
                lexemma = NULL;
                skip_the_voids(input);
                counter++;
            } else {
                string_to_4_cc_in_file(lexemma, output, 4);
                fprintf(output, " ");
                free(lexemma);
                lexemma = NULL;
                skip_the_voids(input);
                counter++;
            }

        }else if(counter % 2 == 0){
            char* lexemma = collect_a_lexemma(input);
            if (lexemma == NULL) {
                fprintf(output, "(too_long_string)");
                free(lexemma);
                lexemma = NULL;
                skip_the_voids(input);
                counter++;
            } else {
                LATIN_to_latin(lexemma, output);
                fprintf(output, " ");
                free(lexemma);
                lexemma = NULL;
                skip_the_voids(input);
                counter++;
            }
        }else if(counter % 5 == 0){
            char* lexemma = collect_a_lexemma(input);
            if (lexemma == NULL) {
                fprintf(output, "(too_long_string)");
                free(lexemma);
                lexemma = NULL;
                skip_the_voids(input);
                counter++;
            } else {
                string_to_8_cc(lexemma, output, 8);
                fprintf(output, " ");
                free(lexemma);
                lexemma = NULL;
                skip_the_voids(input);
                counter++;
            }
        }else{
            char* lexemma = collect_a_lexemma(input);
            if (lexemma == NULL) {
                fprintf(output, "(too_long_string)");
                free(lexemma);
                lexemma = NULL;
                skip_the_voids(input);
                counter++;
            } else {
                fprintf(output, "%s ", lexemma);
                free(lexemma);
                lexemma = NULL;
                skip_the_voids(input);
                counter++;
            }
        }
    }

}

enum flag_a_status_code can_a_flag(char* input_file_name, char* output_file_name){
    FILE* output_file = fopen(output_file_name, "w");
    FILE* input_file = fopen(input_file_name, "r");
    if (!output_file || !input_file) {
        fclose(input_file);
        fclose(output_file);
        return a_file_open_problem;
    }
    else{
        do_a_flag(input_file, output_file);
        fclose(input_file);
        fclose(output_file);
        output_file = NULL, input_file = NULL;
        return a_normal;
    }
}

enum input_status_code analysis(int argc, char** argv){
    if(argc < 2){
        return isc_little_argc;
    }
    else if(!strcmp(argv[1], "-r") || !strcmp(argv[1],  "/r")){
        return isc_r;
    }
    else if(!strcmp(argv[1], "-a") || !strcmp(argv[1],  "/a")){
        return isc_a;
    }
    else{
        return isc_bad_input;
    }
}









