#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <ctype.h>

char* add_base(int base, char* first, char* second){
    long long size_1 = strlen(first);
    long long size_2 = strlen(second);
    long long max_size = (size_1>size_2) ? size_1 : size_2;
    char* sum_str = (char*)malloc(sizeof(char)*(max_size + 1));//1 увеличения 1 для \0
    long long over = 0;
    long long i, j, k;

    for( i = size_1 - 1, j = size_2 - 1, k = max_size - 1; k>=0; i--, j--, k--){
        int digit1 = (i >= 0) ? (isdigit(first[i]) ? first[i] - '0' : toupper(first[i])+10-'A') : 0;
        int digit2 = (j >= 0) ? (isdigit(second[j]) ? second[j] - '0' : toupper(second[j])+10-'A') : 0;
        int summ = digit1 + digit2 + over;
        over = summ / base;
        sum_str[k] = (summ % base > 9) ? (summ % base) + 'A' - 10 : (summ % base) + '0' ;
    }

    if (over > 0) {
        char* newResult = (char*)malloc((max_size + 2) * sizeof(char));  // +3 для учета переноса и завершающего символа '\0'
        if(newResult == NULL){
            return NULL;//дописать enum
        }
        newResult[0] = (over < 10) ? over + '0' : over - 10 + 'A';
        strcpy(newResult + 1, sum_str);
        free(sum_str);
        sum_str = newResult;
        max_size++;
    }

    //int len_ans = strlen(sum_str);
    sum_str[max_size] = '\0';

    return sum_str;

 }

char* adding(int base, int count, ...){
    char* answer = (char*)malloc(sizeof(char)*2);
    if(answer == NULL){
        return NULL;//дописать enum
    }
    answer[0] = '0';
    answer[1] = '\0';
    va_list ptr;
    va_start(ptr, count);
    for(int i = 0; i < count; ++i){
        char* current = va_arg(ptr, char*);
        answer = add_base(base, answer, current);

    }
    va_end(ptr);
    return answer;
}

int main() {
    int base = 10;
    char* first = "10000000";
    char* second = "111";
    char* third = "777";
    char* result = adding(base, 3, first, second, third);
    printf("\n%s\n", result);
}
