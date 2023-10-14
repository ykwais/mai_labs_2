#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "enum.h"
#include "funcs.c"

#define SIZE 30

int main(int argc, char **argv) {
    srand(time(NULL));


    int random[SIZE];
    switch (analysis(argc, argv)) {
        case isc_well:
            //first task
            printf("solving the first task :\n");
            filling_the_array(strtol(argv[1], NULL, 10), strtol(argv[2], NULL, 10), random, SIZE);
            printf("output of the initial fixed-size array:\n");
            print_array(random, SIZE);
            min_max_element_by_one_pass(random, SIZE);
            printf("output of an array with changed max and min values:\n");
            print_array(random, SIZE);
            break;
        case isc_bad_input:
            printf("You have entered many/few arguments. The first task will not be solved\n\n\n");
            break;
        case isc_not_a_number:
            printf("Error entering numbers. The first task will not be solved\n\n\n");
            break;
    }



    //second task
    printf("solving the second task :\n");

    int length_of_a = random_value(5, 7);
    int length_of_b = random_value(2, 4);

    int *a_array = (int *) malloc(sizeof(int) * length_of_a);
    int *b_array = (int *) malloc(sizeof(int) * length_of_b);
    int *c_array = (int *) malloc(sizeof(int) * length_of_a);

    if (a_array == NULL || b_array == NULL || c_array == NULL) {
        printf("Error!");
        free(a_array);
        free(b_array);
        free(c_array);
        a_array = NULL;
        b_array = NULL;
        c_array = NULL;
        return 0;
    }


    filling_the_array(-1000, 1000, a_array, length_of_a);
    filling_the_array(-1000, 1000, b_array, length_of_b);

    printf("output of array A:\n");
    print_array(a_array, length_of_a);

    fast_sort_Lomuto_begin(b_array, length_of_b);
    printf("output of sorted array B:\n");
    print_array(b_array, length_of_b);

    for (int i = 0; i < length_of_a; i++) {
        c_array[i] = a_array[i] + c_value(b_array, length_of_b, a_array[i]);
    }

    printf("output of result array C:\n");
    print_array(c_array, length_of_a);

    free(a_array);
    free(b_array);
    free(c_array);

    a_array = NULL;
    b_array = NULL;
    c_array = NULL;
}
