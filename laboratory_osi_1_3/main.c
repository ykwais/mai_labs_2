#include <stdio.h>
#include "enums.h"
#include "funsc.c"


int main(int argc, char** argv) {
    problems_file status = isc_well;
    switch (analysis(argc, argv)) {
        case isc_bad_input:
            printf("Too little/many arguments");
            break;
        case isc_well:
            switch (task(argv[1], argv[2]))
            {
                case tf_input_trouble:
                    printf("problems opening a file : %s", argv[1]);
                    break;
                case tf_output_trouble:
                    printf("problems opening a file : %s", argv[2]);
                    break;
                case tf_not_the_same:
                    printf("different elements were copied. The process is stoped");
                    break;
                case tf_well:
                    printf("done, master.");
                    break;
            }
            break;
    }
}
