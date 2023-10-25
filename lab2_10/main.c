#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>

typedef long double ld;

typedef long long ll;

typedef enum transformations_status_code{
    tsc_mem_problem,
    tsc_invalid_n,
    tsc_well
}checker;

ld get_value_polynom(ld value, ld** array_coef, int count)
{
    ld result = 0;
    for(int i = count; i >= 0; --i)
    {
        result *= value;
        result += (*array_coef)[i];
    }

    return result;
}

void copy(ld** first, ld** second, int count)
{
    for(int i = 0; i < count; ++i)
    {
        (*second)[i] = (*first)[i];
    }
}

void get_diff_coeffs(ld** input, int count)
{
    for(int i = 1; i < count; ++i)
    {
        (*input)[i] = (*input)[i] * i;
    }
}


void get_g_coeffs(ld a, ld** input, ld** result, int count)
{
    ll fact = 1;
    for(int i = 0; i < count; ++i)
    {

        (*result)[i] += (*input)[i];

        for(int j = i+1; j < count; ++j)
        {

            (*result)[i] += ((*input)[j])*a;

        }
        (*result)[i] /= fact;
        fact *= (i+1);
    }
}


checker collect_new_coeffs(ld a, ld** input, ld** result, int n, ... ) {
    if(n < 0){
        //printf("not polynom\n");
        return tsc_invalid_n;
    }
    int count_coefs = n+1;
    ld *input_coefs = (ld *) malloc(sizeof(ld) * (count_coefs));
    if (input_coefs == NULL) {
        //printf("mem trouble\n");
        return tsc_mem_problem;
    }

    ld *dup_input_coefs = (ld *) malloc(sizeof(ld) * (count_coefs));
    if (dup_input_coefs == NULL) {
        free(input_coefs);
        //printf("mem trouble\n");
        return tsc_mem_problem;
    }

    ld* after_diff_coefs = (ld *) calloc((count_coefs),sizeof(ld));
    if (after_diff_coefs == NULL)
    {
        //printf("mem problem\n");
        free(dup_input_coefs);
        free(input_coefs);
        return tsc_mem_problem;
    }

    va_list ptr;
    va_start(ptr, n);

    for (int i = 0; i < count_coefs; ++i) {
        input_coefs[i] = va_arg(ptr, ld);
    }
    va_end(ptr);


    copy(&input_coefs, &dup_input_coefs, count_coefs);

    ll fact = 1;

    for (int i = 0; i < count_coefs; ++i){
        after_diff_coefs[i] = 
    }


//    get_diff_coeffs(&input_coefs, count_coefs);
//
//    get_g_coeffs(a, &input_coefs, &after_diff_coefs, count_coefs);

    *result = after_diff_coefs;
    *input = dup_input_coefs;

    free(input_coefs);

    return tsc_well;
}

void print_coeffs(ld** input, ld** result, int count)
{
    printf("\ninputted coefs:\n");
    for(int i = 0; i <= count; ++i)
    {
        printf("%Lf  ", (*input)[i]);
    }
    printf("\n");
    printf("resulted coeffs:\n");
    for(int i = 0; i <= count; ++i)
    {
        printf("%Lf  ", (*result)[i]);
    }
    printf("\n\n");
}

int main(){

    ld* input_coefs = NULL;
    ld* result_coeffs = NULL;
    int n = 3;//степень многочлена->правильная
    ld a = 2;
    ld x = 10;


    switch(collect_new_coeffs(a, &input_coefs, &result_coeffs, n, (ld)1,(ld)-2,(ld)3, (ld)4.5)){
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