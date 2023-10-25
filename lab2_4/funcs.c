
#include "helper.h"


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

output is_convex(ld eps, int count, ...)
{
    if(count < 3)
    {
        return osc_no;
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

        if(i == 2){
            previous_triple = current_triple;
        }

        if(!check(eps, &first_vec, &second_vec, &current_triple, &previous_triple)){
            return osc_no;
        }

        second = third;
        first_vec = second_vec;

    }

    second_vec.x = first.x - third.x;
    second_vec.y = first.y - third.y;



    if(!check(eps, &first_vec, &second_vec, &current_triple, &previous_triple)){
        return osc_no;
    }

    first_vec = second_vec;
    second_vec.x = second_classic.x - first.x;
    second_vec.y = second_classic.y - first.y;



    if(!check(eps, &first_vec, &second_vec, &current_triple, &previous_triple)){
        return osc_no;
    }

    va_end(ptr);
    return osc_yes;
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
