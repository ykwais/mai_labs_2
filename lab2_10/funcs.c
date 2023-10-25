
#include "helper.h"

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
    for(int i = 0; i < count; ++i)
    {
        (*input)[i] = (*input)[i+1] * (i+1);
    }
}


ld get_g_coeffs(ld a, ld** input, int count)
{
    ld answer = 0;
    ld x = 1.0L;
    for(int i = 0; i < count; ++i){
        answer += (*input)[i] * x;
        x *= a;
    }
    return answer;
}


checker collect_new_coeffs(ld a, ld** input, ld** result, int n, ... ) {
    if(n < 0){

        return tsc_invalid_n;
    }
    int count_coefs = n+1;
    ld *input_coefs = (ld *) malloc(sizeof(ld) * (count_coefs));
    if (input_coefs == NULL) {

        return tsc_mem_problem;
    }

    ld *dup_input_coefs = (ld *) malloc(sizeof(ld) * (count_coefs));
    if (dup_input_coefs == NULL) {
        free(input_coefs);

        return tsc_mem_problem;
    }

    ld* after_diff_coefs = (ld *) calloc((count_coefs),sizeof(ld));
    if (after_diff_coefs == NULL)
    {

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
        after_diff_coefs[i] = get_g_coeffs(a, &input_coefs, count_coefs - i);//подсчет текущей степени производной
        after_diff_coefs[i] /= fact;
        fact *= (i+1);
        get_diff_coeffs(&input_coefs, count_coefs - i);//берем следующую производную
    }


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