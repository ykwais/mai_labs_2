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
        case isc_not_a_number_x:
            printf("You made a mistake\\typo when entering x, repeat please");
            break;
        case isc_little_eps:
            printf("you have entered too small an epsilon, it should be greater than 1e-20");
            break;
        case isc_large_eps:
            printf("you have entered too large an epsilon, it should be less than 1");
            break;
        case isc_large_x:
            printf("you have entered x greater than 1, so you will be able to calculate only the first two sums. x < 1 and x > -1!!!\n");
            printf("First summ: %.20LF\n", first_summ(strtold(argv[1], NULL), strtold(argv[2], NULL)));
            printf("Second summ: %.20LF\n", second_summ(strtold(argv[1], NULL), strtold(argv[2], NULL)));
            printf("Third summ: diverges\n");
            printf("Fourth summ: diverges\n");
            break;
        case isc_well_x:
            printf("well:\n");
            printf("First summ: %.20LF\n", first_summ(strtold(argv[1], NULL), strtold(argv[2], NULL)));
            printf("Second summ: %.20LF\n", second_summ(strtold(argv[1], NULL), strtold(argv[2], NULL)));
            printf("Third summ: %.20LF\n", third_summ(strtold(argv[1], NULL), strtold(argv[2], NULL)));
            printf("Fourth summ: %.20LF\n", fourth_summ(strtold(argv[1], NULL), strtold(argv[2], NULL)));
            break;

    }

}
