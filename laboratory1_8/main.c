#include <stdio.h>

#include "enums.h"
#include "funcs.c"


int main(int argc, char** argv) {
    switch (analysis(argc, argv)) {
        case isc_well:
            switch(can_flag(argv[1], argv[2])){
                case well:
                    printf("done, master");
                    break;
                case file_open_problem:
                    printf("error: problem file opening");
                    break;
                case not_a_number:
                    printf("wrong number in file! Fix it!");
                    break;
            }
            break;
        case isc_wrong_argc:
            printf("Little/many arguments");
            break;

    }


}
