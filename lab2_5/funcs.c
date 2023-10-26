#include "helper.h"


void add_to_buffer_1(char** buf, int* size_buf, int* written, int* want, char new)
{
    char* tmp = NULL;
    if(*written + *want >= *size_buf){
        *size_buf = (*size_buf*2 > *written + *want) ? *size_buf*2 : (*written + *want)*2;
        if(!(tmp = (char*)realloc(*buf, sizeof(char)*(*size_buf))))
        {
            free(*buf);
            return;//status_code
        }else{
            *buf = tmp;
        }
    }
    for(int i = 0; i < *want; ++i){
        (*buf)[*written+i] = new;
    }
    *written += *want;

}

void add_to_buffer(char** buf, int* size_buf, int* written, int* want, char* new)
{
    char* tmp = NULL;
    if(*written + *want >= *size_buf){
        *size_buf = (*size_buf*2 > *written + *want) ? *size_buf*2 : (*written + *want)*2;
        if(!(tmp = (char*)realloc(*buf, sizeof(char)*(*size_buf))))
        {
            free(*buf);
            return;//status_code
        }else{
            *buf = tmp;
        }
    }
    for(int i = 0; i < *want; ++i){
        (*buf)[*written+i] = new[i];
    }
    *written += *want;

}

int overfprintf(FILE* stream, char* format, ...)
{
    int bl = 0;

    int result_count = 0;

    int amount = 0;

    int length = strlen(format);

    int position = 0;

    int written = 0;

    int size_buf = 1;

    int want_write_amount = 0;

    char* buffer = (char*)malloc(sizeof(char)*(size_buf));

    flag current_flag = u;

    va_list ptr;
    va_start(ptr, format);


    while(format[position] != '\0' && position < length){

        if(format[position] == '%' && (current_flag = type_flag(format+position))!=not_my){
            if(bl){
                want_write_amount = 1;
                add_to_buffer_1(&buffer, &size_buf, &written, &want_write_amount, '\0');

                amount += vfprintf(stream, buffer, ptr);
                buffer[0] = '\0';
                written = 0;
                size_buf = 1;
                bl = 0;

            }

            char* string = NULL;


            switch(current_flag){
                case Ro: {
//                    printf("Ro  ");
//                    printf("%d\n", position);
                    int arg = va_arg(ptr, int);
                    string = int_to_rom(arg, &want_write_amount);

                    break;
                }

                case Zr:{
                    unsigned int arg = va_arg(ptr, unsigned int);
                    string = zeck(arg, &want_write_amount);
                }
//                    printf("Zr  ");
//                    printf("%d\n", position);


                    break;
                case Cv:
                    printf("Cv  ");
                    printf("%d\n", position);


                    break;
                case CV:
                    printf("CV  ");
                    printf("%d\n", position);


                    break;
                case to:
                    printf("to  ");
                    printf("%d\n", position);


                    break;
                case TO:
                    printf("TO  ");
                    printf("%d\n", position);


                    break;
                case mi:
                    printf("mi  ");
                    printf("%d\n", position);


                    break;
                case mu:
                    printf("mu  ");
                    printf("%d\n", position);


                    break;
                case md:
                    printf("md  ");
                    printf("%d\n", position);


                    break;
                case mf:
                    printf("mf  ");
                    printf("%d\n", position);


                    break;

            }
            //want_write_amount = 3;
            add_to_buffer(&buffer, &size_buf, &written, &want_write_amount, string);

            position += 3;
            free(string);
            continue;

        }
        else{
            if(current_flag == not_my){
                bl = 1;
            }

            want_write_amount = 1;
            add_to_buffer_1(&buffer, &size_buf, &written, &want_write_amount, format[position]);

            position++;
            current_flag = u;

        }

    }

    buffer[written] = '\0';
    //printf("\n%s\n", buffer);

    amount += vfprintf(stream, buffer, ptr);

    va_end(ptr);
    return amount;
}

flag type_flag(char* string)
{
    int not_my_length = 0;
    if(string[0] == '%' && string[1] == 'R' && string[2] == 'o' ){

        return Ro;
    }
    if(string[0] == '%' && string[1] == 'Z' && string[2] == 'r' ){

        return Zr;
    }
    if(string[0] == '%' && string[1] == 'C' && string[2] == 'v' ){

        return Cv;
    }
    if(string[0] == '%' && string[1] == 'C' && string[2] == 'V' ){

        return CV;
    }
    if(string[0] == '%' && string[1] == 't' && string[2] == 'o' ){

        return to;
    }
    if(string[0] == '%' && string[1] == 'T' && string[2] == 'O' ){

        return TO;
    }
    if(string[0] == '%' && string[1] == 'm' && string[2] == 'i' ){

        return mi;
    }
    if(string[0] == '%' && string[1] == 'm' && string[2] == 'u' ){

        return mu;
    }if(string[0] == '%' && string[1] == 'm' && string[2] == 'd' ){

        return md;
    }if(string[0] == '%' && string[1] == 'm' && string[2] == 'f' ){

        return mf;
    }

    return not_my;
}

void realloc_char(char** mass, int* size)
{
    char* tmp = NULL;
    *size *= 2;
    if(!(tmp = (char*) realloc(*mass, sizeof(char)*(*size)))){
        free(*mass);
        return;
    }else{
        *mass = tmp;
    }
}

char* int_to_rom(int num, int* amount )
{
    int size = 1;
    char* tmp = (char*) malloc(sizeof(char)*(size+1));
    int counter = 0;

    int norm[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    char* roman[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    int i = 0;

    if (num <= 0) {
        //у них не было отрицательных
        return NULL;
    }

    while (num > 0) {
        while (num >= norm[i]) {


            if(i==11 || i == 1 || i == 3 || i == 5 || i == 7 || i == 9  ){
                counter += 2;
                if(counter >= size){
                    realloc_char(&tmp, &size);
                }
                tmp[counter-2] = roman[i][0];
                tmp[counter-1] = roman[i][1];
                num -= norm[i];

            }else{
                counter++;
                if(counter >= size){
                    realloc_char(&tmp, &size);
                }
                tmp[counter-1] = roman[i][0];
                num -= norm[i];
            }

        }
        i++;
    }
    *amount = counter;
    tmp[counter] = '\0';
    return tmp;
}

unsigned int* fib_row(unsigned int max, int *amount)
{
    int size = 2;
    int counter = 2;
    unsigned int *res = (unsigned int *)malloc(sizeof(unsigned int) * size);
    if (res == NULL)
    {
        return NULL;
    }

    res[0] = 1;
    res[1] = 1;

    while (res[counter - 1] < max)
    {
        unsigned int c = res[counter - 2] + res[counter - 1];

        if (c >= UINT_MAX / 2)
        {
            free(res);
            return NULL;
        }

        if (counter >= size)
        {
            size *= 2;
            unsigned int *tmp = (unsigned int *)realloc(res, sizeof(unsigned int) * size);
            if (tmp == NULL)
            {
                free(res);
                return NULL;
            }
            res = tmp;
        }
        res[counter] = c;
        counter++;
    }
    *amount = counter;
    return res;
}

char* zeck(unsigned int number, int* amount)
{
    if (number >= UINT_MAX / 2)
    {
        return NULL;
    }

    int n = 0;
    unsigned int* fibs = fib_row(number, &n);
    if (fibs == NULL)
    {
        return NULL;/*invalid_input;*/
    }

    char* result = (char *)calloc(n + 2, sizeof(char));
    if (result == NULL)
    {
        free(fibs);
        return NULL;//memory_error;
    }

    //printf("%d", n);
    for (int i = 0; i < n + 1; i++)
    {
        result[i] = '0';
    }

    int i = n - 1;
    int ptr = n - 1;
    while (number != 0)
    {
        if (number >= fibs[i])
        {
            number -= fibs[i];
            result[ptr] = '1';
        }
        i--;
        ptr--;
        if (i < 0)
        {
            free(fibs);
            return NULL;//runtime_error;
        }
    }
    free(fibs);
    result[n] = '1';
    result[n + 1] = '\0';
    *amount = n+1;
    return result;//correct;
}