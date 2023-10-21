#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

void sim(int num) {
    int del = 2;

    while (num > 1) {
        if (num % del == 0) {
            printf("%d ", del);
            num = num / del;
        } else {
            del++;
        }
    }
}

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

void comparison_array_int(int* main, int size1, int* supp, int size2, int pos){
    if(size2 > size1){
        printf("the decimal fraction at this position: %d  -  is not a finite\n", pos+1);
        return;
    }
    for(int i = 0 ; i < size2; ++i){
        if(supp[i] == 1 && main[i] != 1){
            printf("the decimal fraction at this position: %d  -  is not a finite\n", pos+1);
            return;
        }
    }
    printf("the decimal fraction at this position: %d  -  is a finite\n", pos+1);
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
        comparison_array_int(mult_base, length_base, mult_current, length_current, i);
        length_current = 3;
        free(mult_current);

    }
    va_end(ptr);
    free(mult_base);
}



int main() {
    final_representation(36, 5, 0.45, 0.125, 0.12, 0.50, 0.8125);

    sim(36);
    printf("\n");
    sim(25);


}
