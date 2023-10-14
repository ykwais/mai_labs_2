#include <stdio.h>
#include <math.h>
#include <stdarg.h>

long double geometry_middle(int count, ...){
    long double answer = 1.0L;
    va_list ptr;
    va_start(ptr, count);
    for(int i = 0; i < count; ++i){
        answer *= va_arg(ptr, long double);
    }
    va_end(ptr);
    return powl(answer, 1.0L/count);

}

long double fast_pow(long double x, int n){
    if(n < 0){
        return 1.0L/ fast_pow(x, fabsl(n));
    }
    if(n == 0){
        return 1.0L;
    }
    if(n % 2 == 1){
        return fast_pow(x, n-1)*x;
    }
    else{
        long double y = fast_pow(x, n/2);
        return y*y;
    }
}



int main() {
    printf("ans : %.10Lf\n", fast_pow(6.98,3));
    printf("ans : %.10Lf\n", fast_pow(10,3));
    printf("ans_geo : %.10Lf\n", geometry_middle(3, (long double)2, (long double)4, (long double)8));
}
