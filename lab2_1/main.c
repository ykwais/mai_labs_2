#include "helper.h"


int main(int argc, char** argv) {
    char* string = NULL;
    char** new_argv_for_c = NULL;
    unsigned int seed = 0;
    int count_strings = 0;
    memory status = msc_well;
    switch(analysis(argc, argv)){
        case isc_bad_input:
            printf("bad input\n");
            break;
        case isc_l:
            printf("the length of the string passed by the second argument:  %d\n", my_strlen(argv[2]));
            break;
        case isc_r:
            string = reverse_string(argv[2], &status);
            if(status == msc_bad_alloc){
                printf("Problem with memory allocation!");
                return 0;
            }
            printf("the reversed second line passed by the second argument: %s\n", string);
            break;
        case isc_u:
            string = up_half_string(argv[2],&status);
            if(status == msc_bad_alloc){
                printf("Problem with memory allocation!");
                return 0;
            }
            printf("a string with enlarged letters: %s\n", string);
            break;
        case isc_n:
            string = ordered_string(argv[2],&status);
            if(status == msc_bad_alloc){
                printf("Problem with memory allocation!");
                return 0;
            }
            printf("ordered string: %s\n", string);

            break;
        case isc_c:
            switch (arg_to_ud(argv[3], &seed)) {

                case usc_bad_number:
                    printf("You've inputted invalid unsigned int!\n");
                    break;
                case usc_overflow:
                    printf("You've entered too large number, not an unsigned int\n");
                    break;
                case usc_well:

                    srand(seed);

                    count_strings = argc - 3;
                    new_argv_for_c = (char**) malloc(sizeof(char*) * count_strings);
                    if(new_argv_for_c == NULL){
                        printf("Problem with memory allocation!\n");
                        return 0;
                    }
                    new_argv_for_c[0] = argv[2];
                    for(int i = 1; i < count_strings; ++i){
                        new_argv_for_c[i] = argv[3 + i];
                    }

                    string_permutations(new_argv_for_c, count_strings);


                    string = concatenation(new_argv_for_c, count_strings,&status);
                    free(new_argv_for_c);
                    if(status == msc_bad_alloc){
                        printf("Problem with memory allocation!");
                        return 0;
                    }



                    printf("the new concat string: %s\n", string);




                    break;
            }

            break;
    }
    free(string);
}
