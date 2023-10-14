#include <stdio.h>
#include "enums.h"
#include "functions.c"


int main(int argc, char **argv) {
    switch (analysis(argc, argv)) {
        case isc_bad_input:
            printf("You've entered many/few arguments, repeat please");
            break;
        case isc_not_a_number_eps:
            printf("You made a mistake\\typo when entering epsilon, repeat please");
            break;
        case isc_little_eps:
            printf("you have entered too small an epsilon, it should be greater than 1e-20");
            break;
        case isc_large_eps:
            printf("you have entered too large an epsilon, it should be less than 1");
            break;
        case isc_well:
            printf("well:\n");
            printf("First integral: %.20LF\n",
                   the_parabola_method(strtold(argv[1], NULL), 0.0L, 1.0L, &first_function));
            printf("Second integral: %.20LF\n",
                   the_parabola_method(strtold(argv[1], NULL), 0.0L, 1.0L, &second_function));
            printf("Third integral: %.20LF\n",
                   the_parabola_method(strtold(argv[1], NULL), 0.0L, 1.0L, &third_function));
            printf("Fourth integral: %.20LF\n",
                   the_parabola_method(strtold(argv[1], NULL), 0.0L, 1.0L, &fourth_function));
            break;
    }
}