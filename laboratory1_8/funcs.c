#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "enums.h"



void skip_the_voids(FILE *file_name) {
    int ch;
    while ((ch = fgetc(file_name)) != EOF) {
        if (ch != 32 && ch != 9 && ch != 10) {
            ungetc(ch, file_name);
            break;
        }
    }
}

char *collect_a_lexemma(FILE *file_name, enum troubles_with_lexemma* stat) {
    int length = 2;
    char *lexemma = (char *) malloc(sizeof(char) * length);
    if (lexemma == NULL) {
        return NULL;
    }
    int ch;

    int index = 0;
    char *tmp = NULL;

    while ((ch = fgetc(file_name)) != EOF) {
        if (ch == 10 || ch == 9 || ch == 32) {
            break;
        }
        if (length <= index)
        {
            length <<= 1;

            if (!(tmp = (char*) realloc(lexemma, sizeof (char) * length)))
            {
                free(lexemma);
                *stat = twl_troubles;
                return NULL;
            }
            else
            {
                lexemma = tmp;
            }
        }

        lexemma[index++] = ch;
    }

    if (!(tmp = (char*) realloc(lexemma, sizeof (char) * (index + 1))))
    {
        free(lexemma);
        *stat = twl_troubles;
        return NULL;
    }
    else
    {
        lexemma = tmp;
    }
    lexemma[index] = '\0';
    return lexemma;
}

int length_long_long(long long number){
    char random_string[20];
    sprintf(random_string, "%lld",number);

    return (int)strlen(random_string);
}

long long string_cc_to_10CC(int base, char *string, enum overflow* status_overflow) {//здесь буду отслеживать переполнение
    bool negative = false;
    char *ptr = string;
    long long result = 0;
    while (*ptr) {
        if(*ptr == 45){
            negative = true;
            ptr++;
            continue;
        }
        if(length_long_long(result) > 17 ){
            *status_overflow = overflow;
            break;
        }
        result = result * base + (isdigit(*ptr) ? *ptr - '0' : *ptr - 'A' + 10);
        ptr++;
    }

    if(negative)
    {
        return -1*result;
    }
    return result;

}

void divided_string(char *arg, FILE *output) {
    int length = strlen(arg);
    char *tmp = (char *) malloc(sizeof(char) * length);
    if(tmp == NULL){
        printf("Troubles with opening file!");
        return;
    }

    int counter = 0;
    int counter_2 = 0;
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
            counter_2++;
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

    tmp[length - counter_2] = '\0';

    if (tmp[0] == '\0') {
        fprintf(output, "!0");
    } else {
        for (int i = 0; i < length - counter_2; i++) {
            fprintf(output, "%c", tmp[i]);
        }
    }


    fprintf(output, " ");
    free(tmp);
    tmp = NULL;
}

char *to_upper_text(char *string) {
    int length = strlen(string);
    char *tmp = (char *) malloc(sizeof(char) * (length+1));
    if (tmp == NULL) {
        return NULL;
    }

    for (int i = 0; i < length; i++) {
        tmp[i] = toupper(string[i]);
    }
    tmp[length] = '\0';
    return tmp;
}

int min_cc(char *string) {
    int max = 1;
    int length = strlen(string);
    for (int i = 0; i < length; i++) {
        if (isdigit(string[i]) && string[i] - '0' >= max) {
            max = string[i] - '0';
        } else if (isupper(string[i]) && string[i] - 'A' + 10 >= max ) {
            max = string[i] - 'A' + 10;
        } else {
            continue;
        }
    }

    return max + 1;

}


bool is_number(char *string) {

    int length = strlen(string);

    for (int i = 0; i < length; i++) {
        int x = string[i];
        if (!isalnum(x) && !(string[i] == '-' && i == 0)) {
            return false;
        }
        if(length == 1 && string[i] == '-'){
            return false;
        }

    }
    return true;
}


void do_flag(FILE *input, FILE *output, enum flag_status_code *is_num, enum overflow* status_overflow) {
    skip_the_voids(input);
    enum troubles_with_lexemma status_trouble_lexemma = twl_no_troubles;
    while (!feof(input)) {
        char *lexemma = collect_a_lexemma(input, &status_trouble_lexemma);

        if (!is_number(lexemma)) {
//            fclose(output);
//            fopen(output, "w");
//            fclose(output);
            *is_num = not_a_number;
            break;
        }
        if (lexemma == NULL && status_trouble_lexemma == twl_troubles) {
            status_trouble_lexemma = twl_no_troubles;
            printf("");
            skip_the_voids(input);
            lexemma = NULL;
        } else {
            char* upper_lexemma = to_upper_text(lexemma);
            divided_string(upper_lexemma, output);

            int minim_cc = min_cc(upper_lexemma);
            *status_overflow = not_overflow;
            long long number_in_10cc = string_cc_to_10CC(minim_cc, upper_lexemma, status_overflow);
            fprintf(output, "%d ", minim_cc);
            if(*status_overflow == overflow){
                fprintf(output, "Overflow\n");
                *status_overflow = not_overflow;
            }else {
                fprintf(output, "%lld\n", number_in_10cc);
            }



            free(lexemma);

            free(upper_lexemma);


            skip_the_voids(input);
        }
    }

}

enum flag_status_code can_flag(char *input_file_name, char *output_file_name) {
    FILE *output_file = fopen(output_file_name, "w");
    FILE *input_file = fopen(input_file_name, "r");

    if (!output_file || !input_file) {
        fclose(input_file);

        fclose(output_file);
        return file_open_problem;
    } else {
        enum flag_status_code is_num;
        enum overflow sts;
        do_flag(input_file, output_file, &is_num, &sts);

        if (is_num == not_a_number) {
            return not_a_number;
        }
        fclose(input_file);

        fclose(output_file);
        output_file = NULL, input_file = NULL;
        return well;
    }
}

enum input_status_code analysis(int argc, char** argv){
    if(argc != 3){
        return isc_wrong_argc;
    }

    else{
        return isc_well;
    }
}