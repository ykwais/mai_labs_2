
#include "helper.h"



int main(){

    ld* input_coefs = NULL;
    ld* result_coeffs = NULL;
    int n = 6;//степень многочлена->правильная
    ld a = 4;
    ld x = 10;


    switch(collect_new_coeffs(a, &input_coefs, &result_coeffs, n, (ld)1,(ld)-2,(ld)3, (ld)4.5, (ld)78, (ld)-23, (ld)9)){
        case tsc_mem_problem:
            printf("Problem with memory allocation\n");
            break;
        case tsc_invalid_n:
            printf("You've entered wrong degree!\n");
            break;
        case tsc_well:
            print_coeffs(&input_coefs, &result_coeffs, n);
            printf("check for first: %Lf\n", get_value_polynom(x, &input_coefs, n));
            printf("check for second: %Lf\n", get_value_polynom(x-a, &result_coeffs, n));
            break;
    }

    free(result_coeffs);
    free(input_coefs);

}