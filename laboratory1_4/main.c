#include <stdio.h>
#include "enum.h"
#include "functions.c"



int main(int argc, char** argv) {
    char* out = NULL;
    char* input = argv[2];
    switch (check_n(argv[1])) {
        case in_yes:
            out = argv[3];
            break;
        case in_not:

            out = create_output_file(argv[2]);
            break;
        case in_wrong_num:
            printf("wrong  flag");
            return 0;

    }
    switch (analysis(argc, argv)) {
        case isc_d:
            without_arabic_n_mode(input, out);
            printf("everything is done, master");
            break;
        case isc_i:
            counter_latin_n_mode(input, out);
            printf("everything is done, master");
            break;
        case isc_s:
            counter_not_latin_n_mode(input, out);
            printf("everything is done, master");
            break;
        case isc_a:
            liters_to_16CC_n_mode(input, out);
            printf("everything is done, master");
            break;
        case isc_bad_input:
            printf("bad_input");
            break;

    }

    free(out);
    free(input);

//    char* out = NULL;
//    switch (analysis(argc, argv)) {
//        case isc_bad_input:
//            printf("You've entered the wrong flag!");
//            break;
//        case isc_d:
//            switch (enum_is_open_file_read(argv[2])) {
//                case iofr_yes:
//                    out = create_output_file(argv[2]);
//                    without_arabic_n_mode(argv[2], out);
//                    free(out);
//                    printf("everything is done, master");
//                    break;
//                case iofr_not:
//                    printf("problems opening the input file!");
//                    break;
//            }
//            break;
//        case isc_i:
//            switch (enum_is_open_file_read(argv[2])) {
//                case iofr_yes:
//                    out = create_output_file(argv[2]);
//                    counter_latin_n_mode(argv[2], out);
//                    free(out);
//                    printf("everything is done, master");
//                    break;
//                case iofr_not:
//                    printf("problems opening the input file!");
//                    break;
//            }
//            break;
//        case isc_s:
//            switch (enum_is_open_file_read(argv[2])) {
//                case iofr_yes:
//                    out = create_output_file(argv[2]);
//                    counter_not_latin_n_mode(argv[2], out);
//                    free(out);
//                    printf("everything is done, master");
//                    break;
//                case iofr_not:
//                    printf("problems opening the input file!");
//                    break;
//            }
//            break;
//        case isc_a:
//            switch (enum_is_open_file_read(argv[2])) {
//                case iofr_yes:
//                    out = create_output_file(argv[2]);
//                    liters_to_16CC_n_mode(argv[2], out);
//                    free(out);
//                    printf("everything is done, master");
//
//                    break;
//                case iofr_not:
//                    printf("problems opening the input file!");
//                    break;
//            }
//            break;
//        case isc_nd:
//            switch (enum_is_open_file_read(argv[2])) {
//                case iofr_yes:
//                    switch (enum_is_open_file_write(argv[3])) {
//                        case iofw_yes:
//                            without_arabic_n_mode(argv[2], argv[3]);
//                            printf("everything is done, master");
//                            break;
//                        case iofw_not:
//                            printf("problems opening the output file");
//                            break;
//
//                    }
//                    break;
//                case iofr_not:
//                    printf("problems opening the input file!");
//                    break;
//            }
//            break;
//        case isc_ni:
//            switch (enum_is_open_file_read(argv[2])) {
//                case iofr_yes:
//                    switch (enum_is_open_file_write(argv[3])) {
//                        case iofw_yes:
//                            counter_latin_n_mode(argv[2], argv[3]);
//                            printf("everything is done, master");
//                            break;
//                        case iofw_not:
//                            printf("problems opening the output file");
//                            break;
//
//                    }
//                    break;
//                case iofr_not:
//                    printf("problems opening the input file!");
//                    break;
//            }
//            break;
//        case isc_ns:
//            switch (enum_is_open_file_read(argv[2])) {
//                case iofr_yes:
//                    switch (enum_is_open_file_write(argv[3])) {
//                        case iofw_yes:
//                            counter_not_latin_n_mode(argv[2], argv[3]);
//                            printf("everything is done, master");
//                            break;
//                        case iofw_not:
//                            printf("problems opening the output file");
//                            break;
//
//                    }
//                    break;
//                case iofr_not:
//                    printf("problems opening the input file!");
//                    break;
//            }
//            break;
//        case isc_na:
//            switch (enum_is_open_file_read(argv[2])) {
//                case iofr_yes:
//                    switch (enum_is_open_file_write(argv[3])) {
//                        case iofw_yes:
//                            liters_to_16CC_n_mode(argv[2], argv[3]);
//                            printf("everything is done, master");
//                            break;
//                        case iofw_not:
//                            printf("problems opening the output file");
//                            break;
//
//                    }
//                    break;
//                case iofr_not:
//                    printf("problems opening the input file!");
//                    break;
//            }
//            break;
//    }


}
