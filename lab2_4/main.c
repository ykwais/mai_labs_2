#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <math.h>

typedef long double ld;

typedef struct{
    ld x;
    ld y;
} point;

bool is_zero(ld eps, point f, point s){
    if((fabsl(f.x) < eps && fabsl(f.y) < eps) || (fabsl(s.x) < eps && fabsl(s.y) < eps) || (fabsl(f.x) < eps && fabsl(s.x) < eps) || (fabsl(f.y) < eps && fabsl(s.y) < eps) )
    {
        return true;
    }

    return false;
}

bool check(ld eps, point* first, point* second, ld* curr, ld* prev){
    if(is_zero(eps, *first, *second)){
        return false;//два подряд вектора лежат на одной прямой.
    }
    if(*prev == 0){
        *prev = (*first).x * (*second).y - (*second).x * (*first).y;
    }else{
        *prev = *curr;
    }

    *curr = (*first).x * (*second).y - (*second).x * (*first).y;
    if((*prev) * (*curr) < 0){
        return false;//разные тройки
    }

    return true;
}

bool is_convex(ld eps, int count, ...)
{
    if(count < 3)
    {
        return false;
    }

    va_list ptr;
    va_start(ptr, count);

    point first = va_arg(ptr, point);
    point second = va_arg(ptr, point);

    point second_classic = second;

    point third = {0 , 0};

    point first_vec = {second.x - first.x, second.y - first.y};
    point second_vec = {0,0};

    ld current_triple = 0;
    ld previous_triple = 0;

    for(int i = 2; i < count; ++i)
    {
        third = va_arg(ptr, point);

        second_vec.x = third.x - second.x;
        second_vec.y = third.y - second.y;
//        if(is_zero(eps, first_vec, second_vec)){
//            return false;//два подряд вектора лежат на одной прямой.
//        }
//
//        previous_triple = current_triple;
//        current_triple = first_vec.x * second_vec.y - second_vec.x * first_vec.y;
        if(i == 2){
            previous_triple = current_triple;
        }

        if(!check(eps, &first_vec, &second_vec, &current_triple, &previous_triple)){
            return false;
        }
//        if(previous_triple * current_triple < 0){
//            return false;//разные тройки
//        }
        second = third;
        first_vec = second_vec;

    }

    second_vec.x = first.x - third.x;
    second_vec.y = first.y - third.y;

//    if(is_zero(eps, first_vec, second_vec)){
//        return false;//два подряд вектора лежат на одной прямой.
//    }
//    previous_triple = current_triple;
//    current_triple = first_vec.x * second_vec.y - second_vec.x * first_vec.y;
//    if(previous_triple * current_triple < 0){
//        return false;//разные тройки
//    }

    if(!check(eps, &first_vec, &second_vec, &current_triple, &previous_triple)){
        return false;
    }

    first_vec = second_vec;
    second_vec.x = second_classic.x - first.x;
    second_vec.y = second_classic.y - first.y;

//    if(is_zero(eps, first_vec, second_vec)){
//        return false;//два подряд вектора лежат на одной прямой.
//    }
//    previous_triple = current_triple;
//    current_triple = first_vec.x * second_vec.y - second_vec.x * first_vec.y;
//    if(previous_triple * current_triple < 0){
//        return false;//разные тройки
//    }

    if(!check(eps, &first_vec, &second_vec, &current_triple, &previous_triple)){
        return false;
    }

    va_end(ptr);
    return true;
}

ld polynom(double value, int n, ...){
    ld answer = 0.0L;
    ld next = 0.0L;
    va_list ptr;
    va_start(ptr, n);

    if(n < 1){
        return answer;
    }

    for(int i = 0; i <= n; ++i){
        answer *= value;
        next = va_arg(ptr, ld);
        answer += next;
    }

    va_end(ptr);
    return answer;

}



int main() {
    if(is_convex(0.0000000001L, 4, (point){3,2},(point){2,3},(point){2,1}, (point){4,1} )){
        printf("yes\n");
    }else{
        printf("no\n");
    }

    printf("%Lf\n", polynom(10, 2, (ld)4,(ld)3, (ld)5));

}
