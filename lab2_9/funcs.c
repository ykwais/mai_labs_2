#include "helper.h"

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

int* simple_mult(long long number, int* length, memory* stata)
{
    *stata = msc_well;
    int* tmp = NULL;
    int* result = (int*)calloc((*length), sizeof(int) );
    if(result == NULL){
        *stata = msc_problem;
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
                    free(result);//
                    *stata = msc_problem;
                    return NULL;
                }
                else
                {
                    result = tmp;
                    for(int i = 0; i < *length; ++i){
                        if(result[i] != 1){
                            result[i] = 0;
                        }
                    }

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
    memory stat = msc_well;
    //set от base
    int length_base = 3, length_current = 3;
    int* mult_base = simple_mult(base, &length_base, &stat);
    if(stat == msc_problem){
        printf("Problems with memory allocation!\n");
        return;
    }
    va_list ptr;
    va_start(ptr, count);
    for(int i = 0; i < count; ++i)
    {
        double current = va_arg(ptr, double);
        long long den = get_denominator(current);
        int* mult_current = simple_mult(den, &length_current, &stat);
        if(stat == msc_problem){
            printf("Problems with memory allocation!\n");
            return;
        }
        comparison_array_int(mult_base, length_base, mult_current, length_current, i);
        length_current = 3;
        free(mult_current);

    }
    va_end(ptr);
    free(mult_base);
}
