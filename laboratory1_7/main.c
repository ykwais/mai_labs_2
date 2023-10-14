#include <stdio.h>
#include "enums.h"
#include "funcs.c"

int main(int argc, char** argv){
    switch (analysis(argc, argv)) {
        case isc_bad_input:
            break;
        case isc_little_argc:
            break;
        case isc_r:
            switch(can_r_flag(argv[3], argv[4], argv[argc-1])){
                case r_normal:
                    printf("done, master");
                    break;
                case r_file_open_problem:
                    printf("error: problem file opening");
                    break;
            }
            break;
        case isc_a:
            switch(can_a_flag(argv[3], argv[argc-1])){
                case a_normal:
                    printf("done, master");
                    break;
                case a_file_open_problem:
                    printf("error: problem file opening");
                    break;
            }
            break;
    }



}