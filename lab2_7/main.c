#include <stdio.h>
#include <math.h>
#include <string.h>

long double func_1(long double x){
    return log(x) - 1.0L;
}

long double func_2(long double x){
    return cosl(x) - expl(((x*x)/(-2.0L))) + x - 1;
}

//long double func_3(long double x){
//    return tanl(x/2)+
//}



long double dich(long double left, long double right, long double eps, long double(*function)(long double)){

    long double answer;
    long double middle;
    do{
        middle = (left + right) / 2;
        answer = function(middle);
        if(answer < 0L){ //это не сравнение! это проверка на отрицательность!!!!
            left = middle;
        }
        else{
            right = middle;
        }
    } while (fabsl(left - right) > eps);

    return middle;

}

int main() {
    printf("Solution by dichotomy: %Lf\n", dich((long double)2, (long double)3,(long double)0.00001, &func_1) );
    printf("Solution by dichotomy: %Lf\n", dich((long double)1, (long double)2,(long double)0.0000001, &func_2) );

}
