#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>



int* simple_mult(long long number, int* length)
{
    int* tmp = NULL;
    int* result = (int*)calloc((*length), sizeof(int) );
    if(result == NULL){
        return NULL;//enum-чик
    }
    int delit = 2;
    while(number > 1)
    {
        if(number % delit == 0)
        {
            if(delit >= *length){
                *length = delit +1;
                if (!(tmp = (int*) realloc(result, sizeof (int) * (*length))))
                {
                    free(result);

                    return NULL;
                }
                else
                {
                    result = tmp;

                }
            }
            result[delit] = 1;
            number /= delit;
        }else{
            delit++;
        }
    }
    return result;
}

long long gcd(long long a, long long b){
    if(b == 0){
        return a;
    }else{
        return gcd(b, a % b);
    }
}

long long get_denominator(double number)
{
    long long numerator = number * 1e15;
    long long denominator = 1e15;

    long long nod = gcd(numerator, denominator);

    numerator /= nod;
    denominator /= nod;

    return denominator;
}

void final_representation(long long base, int count, ...)
{
    //set от base
    int length_base = 3, length_current = 3;
    int* mult_base = simple_mult(base, &length_base);
    va_list ptr;
    va_start(ptr, count);
    for(int i = 0; i < count; ++i)
    {
        double current = va_arg(ptr, double);
        long long den = get_denominator(current);
        int* mult_current = simple_mult(den, &length_current);

        length_current = 3;
        free(mult_current);
        //printf("%lld\n", den);
    }
    va_end(ptr);
    free(mult_base);
}



int main() {
    final_representation(10, 5, 0.45, 0.125, 0.12, 0.50, 0.8125);
//    simplify(997);
    int len = 3;
    int* ans = simple_mult(81, &len);
    printf("\n");
    printf("\n");
    for(int i = 0; i < len; ++i){
        printf("%d  ", ans[i]);
    }
    //printf("\n%d\n", ans[len+6]);
    printf("\n");

}
