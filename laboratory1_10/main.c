#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "enums.h"
#include "functions.c"

#define SIZE 65

int main() {
    int counter = 0;
    long long max = LLONG_MIN;
    long long tmp = 0;
    int negative = 0;
    char max_latin[SIZE];
    char result_string_of_max[SIZE];
    char buf[SIZE+1];
    bool number = false;

    printf("Please enter the base of the number system:\n");
    int base;
    scanf("%d", &base);
    switch (is_well_base(&base)) {
        case iscb_bad:
            printf("The base of the number system should be >= 2 and <= 36!");
            break;
        case iscb_well:
            printf("Enter your numbers, after the end of the input, enter Stop:\n");
            char string_of_number[SIZE];
            scanf("%s", &string_of_number);

            while (strcmp(string_of_number, "Stop")) {

                if (string_of_number[0] == '-') {
                    negative = 1;
                } else {
                    negative = 0;
                }
                if(acceptable_value_of_cc(base, string_of_number)){
                    number = true;
                    tmp = string_cc_to_10CC(base, string_of_number, negative);
                    if (llabs(tmp) >= llabs(max)) {
                        max = tmp;

                        for(int i = 0; i < SIZE; i++){
                            max_latin[i] = string_of_number[i];
                        }
                    }

                    scanf("%s", &string_of_number);
                }else{

                    printf("You've entered the wrong number! Repeat this entering, please\n");
                    scanf("%s", &string_of_number);
                }



            }
            if(!number){
                printf("Error");
                return 0;
            }
            printf("The maximum modulo number :  %s\n", max_latin);
            divided_string(max_latin, result_string_of_max);
            printf("The maximum modulo number without leading zeros : %s\n", result_string_of_max);
            printf("The maximum modulo number in decimal notation : %lld\n", max);

            printf("The maximum modulo number in the 9th number system : ");
            cc10_to_base_cc(9, max, &counter, buf );
            print_diff_cc(counter, buf);

            printf("The maximum modulo number in the 18th number system : ");
            cc10_to_base_cc(18, max, &counter, buf );
            print_diff_cc(counter, buf);

            printf("The maximum modulo number in the 27th number system : ");
            cc10_to_base_cc(27, max,&counter, buf );
            print_diff_cc(counter, buf);

            printf("The maximum modulo number in the 36th number system : ");
            cc10_to_base_cc(36, max,&counter, buf );
            print_diff_cc(counter, buf);
            break;

    }

}

