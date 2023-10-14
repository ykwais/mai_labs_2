
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "enum.h"

#define SIZE 33


//enum input_status_code analysis(int argc, char **argv, char* output_file_name) {
//    if (argc < 3 || argc > 4) {
//        return isc_bad_input;
//    } else if (!strcmp(argv[1], "-help") || !strcmp(argv[1], "/help")) {
//        return isc_need_help;
//    } else if (argc == 3) {
//
//        if (!strcmp(argv[1], "-d") || !strcmp(argv[1], "/d")) {
//            return isc_d;
//        } else if (!strcmp(argv[1], "-i") || !strcmp(argv[1], "/i")) {
//            return isc_i;
//        } else if (!strcmp(argv[1], "-s") || !strcmp(argv[1], "/s")) {
//            return isc_s;
//        } else if (!strcmp(argv[1], "-a") || !strcmp(argv[1], "/a")) {
//            return isc_a;
//        } else {
//            return isc_bad_input;
//        }
//    } else if (argc == 4) {
//        if (!strcmp(argv[1], "-nd") || !strcmp(argv[1], "/nd")) {
//            return isc_nd;
//        } else if (!strcmp(argv[1], "-ni") || !strcmp(argv[1], "/ni")) {
//            return isc_ni;
//        } else if (!strcmp(argv[1], "-ns") || !strcmp(argv[1], "/ns")) {
//            return isc_ns;
//        } else if (!strcmp(argv[1], "-na") || !strcmp(argv[1], "/na")) {
//            return isc_na;
//        } else {
//            return isc_bad_input;
//        }
//    }
//}

enum is_open_file_read enum_is_open_file_read(char *file_name) {
    FILE *filename = NULL;
    if (!(filename = fopen(file_name, "r"))) {
        return iofr_not;//здесь не закрываю, так как в этом месте файл и не открылся
    } else {
        fclose(filename);
        return iofr_yes;
    }
}

enum is_open_file_write enum_is_open_file_write(char *file_name) {
    FILE *filename = NULL;
    if (!(filename = fopen(file_name, "w"))) {
        return iofw_not;//здесь не закрываю, так как в этом месте файл и не открылся
    } else {
        fclose(filename);
        return iofw_yes;
    }
}


char *create_output_file(char *input_file_name) {
    int length = strlen(input_file_name);
    int out_length = length;
    char *output_file_name = (char *) malloc(out_length * 2);
    if (output_file_name == NULL) {
        return NULL;
    }
    while (input_file_name[length] != '\\' && length) {
        length--;
    }
    if (length == 0) {
        output_file_name[length] = 'o';
        output_file_name[length + 1] = 'u';
        output_file_name[length + 2] = 't';
        output_file_name[length + 3] = '_';
        for (int i = length + 4; i < out_length + 4; i++) {
            output_file_name[i] = input_file_name[i - 4];
        }
        output_file_name[out_length + 4] = '\0';
    } else {
        for (int i = 0; i < length + 1; i++) {
            output_file_name[i] = input_file_name[i];
        }
        output_file_name[length + 1] = 'o';
        output_file_name[length + 2] = 'u';
        output_file_name[length + 3] = 't';
        output_file_name[length + 4] = '_';

        for (int i = length + 5; i < out_length + 4; i++) {
            output_file_name[i] = input_file_name[i - 4];
        }
        output_file_name[out_length + 4] = '\0';
    }
    return output_file_name;
}


void without_arabic_n_mode(char *input_file_name, char *output_file_name) {
    FILE *input_file = NULL;
    FILE *output_file = NULL;
    if (!(output_file = fopen(output_file_name, "w"))) {
        printf("Error!");
    }
    if (!(input_file = fopen(input_file_name, "r"))) {
        printf("Error!");
    } else {
        int ch;
        while ((ch = fgetc(input_file)) != EOF) {
            if (ch >= 48 && ch <= 57) {
                continue;
            }
            fprintf(output_file, "%c", ch);
        }
    }
    fclose(input_file);
    fclose(output_file);
}


void liters_to_16CC_n_mode(char *input_file_name, char *output_file_name) {
    FILE *input_file = NULL;
    FILE *output_file = NULL;
    if (!(output_file = fopen(output_file_name, "w"))) {
        printf("Error!");
    }
    if (!(input_file = fopen(input_file_name, "r"))) {
        printf("Error!");
    } else {
        int ch;
        while ((ch = fgetc(input_file)) != EOF) {
            if (ch >= 48 && ch <= 57) {
                fprintf(output_file, "%c", ch);
                continue;
            } else {
                int r;
                int base = 16;
                char buf[SIZE];
                char *ptr = buf + SIZE - 1;
                *ptr = 0;
                ptr--;
                int counter = 0;
                while (ch > 0) {
                    r = ch % base;
                    *ptr = (r > 9) ? r - 10 + 'A' : r + 48;
                    ptr--;
                    ch /= base;
                    counter++;
                }
                for (int i = SIZE - counter - 1; i < SIZE - 1; i++) {
                    fprintf(output_file, "%c", buf[i]);
                }
            }
        }
    }
    fclose(input_file);
    fclose(output_file);
}


void counter_latin_n_mode(char *input_file_name, char *output_file_name) {
    FILE *input_file = NULL;
    FILE *output_file = NULL;
    if (!(output_file = fopen(output_file_name, "w"))) {
        printf("Error!");
    }
    if (!(input_file = fopen(input_file_name, "r"))) {
        printf("Error!");
    } else {
        unsigned long counter_str = 1;
        unsigned long counter_latin = 0;
        int ch;
        while ((ch = fgetc(input_file)) != EOF) {
            if (ch == 10) {
                fprintf(output_file, "%lu:  %lu\n", counter_str, counter_latin);
                counter_str++;
                counter_latin = 0;
                continue;
            }
            if ((ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122)) {
                counter_latin++;
                continue;
            }

        }
        fprintf(output_file, "%lu:  %lu\n", counter_str, counter_latin);
    }
    fclose(input_file);
    fclose(output_file);
}


void counter_not_latin_n_mode(char *input_file_name, char *output_file_name) {
    FILE *input_file = NULL;
    FILE *output_file = NULL;
    if (!(output_file = fopen(output_file_name, "w"))) {
        printf("Error!");
    }
    if (!(input_file = fopen(input_file_name, "r"))) {
        printf("Error!");
    } else {
        unsigned long counter_str = 1;
        unsigned long counter_not_latin_arabic_space = 0;
        int ch;
        while ((ch = fgetc(input_file)) != EOF) {
            if (ch == 10) {
                fprintf(output_file, "%lu:  %lu\n", counter_str, counter_not_latin_arabic_space);
                counter_str++;
                counter_not_latin_arabic_space = 0;
                continue;
            }
            if (ch != 32 && (ch < 65 || ch > 90) && (ch < 97 || ch > 122) && (ch < 48 || ch > 57)) {
                counter_not_latin_arabic_space++;
                continue;
            }

        }
        fprintf(output_file, "%lu:  %lu\n", counter_str, counter_not_latin_arabic_space);
    }
    fclose(input_file);
    fclose(output_file);
}

enum input_status_code analysis(int argc, char **argv) {
    if (argc < 3 || argc > 4) {
        return isc_bad_input;
    }
    if(argc == 3 && argv[1][1] == 'n') {
        return isc_bad_input;
    }
    if(argc == 4 && argv[1][1] != 'n'){
        return isc_bad_input;
    }
    if (!strcmp(argv[1], "-help") || !strcmp(argv[1], "/help")) {
        return isc_need_help;
    } else if (argc == 3 || argc == 4) {

        if (!strcmp(argv[1], "-d") || !strcmp(argv[1], "/d") || !strcmp(argv[1], "-nd") || !strcmp(argv[1], "/nd")) {
            return isc_d;
        } else if (!strcmp(argv[1], "-i") || !strcmp(argv[1], "/i") || !strcmp(argv[1], "-ni") ||
                   !strcmp(argv[1], "/ni")) {
            return isc_i;
        } else if (!strcmp(argv[1], "-s") || !strcmp(argv[1], "/s") || !strcmp(argv[1], "-ns") ||
                   !strcmp(argv[1], "/ns")) {
            return isc_s;
        } else if (!strcmp(argv[1], "-a") || !strcmp(argv[1], "/a") || !strcmp(argv[1], "-na") ||
                   !strcmp(argv[1], "/na")) {
            return isc_a;
        } else {
            return isc_bad_input;
        }
    }
//    } else if (argc == 4) {
//        if (!strcmp(argv[1], "-nd") || !strcmp(argv[1], "/nd")) {
//            return isc_nd;
//        } else if (!strcmp(argv[1], "-ni") || !strcmp(argv[1], "/ni")) {
//            return isc_ni;
//        } else if (!strcmp(argv[1], "-ns") || !strcmp(argv[1], "/ns")) {
//            return isc_ns;
//        } else if (!strcmp(argv[1], "-na") || !strcmp(argv[1], "/na")) {
//            return isc_na;
//        } else {
//            return isc_bad_input;
//        }
//    }
}


enum input_n check_n(char *first_arg) {
    if (strlen(first_arg) == 3 && first_arg[1] == 'n') {
        return in_yes;
    }
    if (strlen(first_arg) == 2 && first_arg[1] != 'n') {
        return in_not;
    }
    return in_wrong_num;
}


