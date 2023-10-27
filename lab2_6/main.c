#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

typedef long long ll;

typedef enum flag_status_code{
    Ro,
    Zr,
    Cv,
    CV,
    not_my,
    u
}flag;

flag type_flag(char* string);
int overfscanf(FILE* stream, char* format, ...);

int main() {
    int d;

    overfscanf(stdin, "sdf %Cv", &d,21);

    printf("%d\n", d);
}


flag type_flag(char* string)
{

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
    return not_my;
}

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



bool is_lower_alpha(char c){
    return (c >= 97 && c <= 122);
}

int length_long_long(long long number){
    char random_string[20];
    sprintf(random_string, "%lld",number);

    return (int)strlen(random_string);
}

ll string_cc_to_10CC_lower(char *string, int base, int* amount) {//здесь буду отслеживать переполнение
    if(base > 36 || base < 2){
        base = 10;
    }
    bool negative = false;
    char *ptr = string;
    long long result = 0;
    int count = 0;

    while (*ptr) {
        if(isdigit(*ptr) || is_lower_alpha(*ptr) || (*ptr == 45 && count == 0)){
            if(*ptr == 45 && count == 0){
                negative = true;
                ptr++;
                count++;
                continue;
            }
            if(length_long_long(result) > 17 ){
                //overflow

                return result;
            }
            result = result * base + (isdigit(*ptr) ? *ptr - '0' : *ptr - 'a' + 10);
            ptr++;
            count++;
        }
        else{

            return result;
        }

    }

    if(negative)
    {
        result *= -1;
    }


    return result;

}

int overfscanf(FILE* stream, char* format, ...)
{
    int bl = 0;

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

                amount += vfscanf(stream, buffer, ptr);
                buffer[0] = '\0';
                written = 0;
                size_buf = 1;
                bl = 0;

            }

            //char* string = NULL;


            switch(current_flag){
                case Ro: {
                    int arg = va_arg(ptr, int);
                    //string = int_to_rom(arg, &want_write_amount);
                    break;
                }

                case Zr:{
                    unsigned int arg = va_arg(ptr, unsigned int);
                    //string = zeck(arg, &want_write_amount);
                    break;
                }
                case Cv: {
                    int* number = va_arg(ptr, int*);
                    int base = va_arg(ptr, int);
                    char tmp[65];
                    fscanf(stream, "%s", tmp);
                    *number = string_cc_to_10CC_lower(tmp, base, &want_write_amount);
                    break;
                }


                case CV:{
                    int number = va_arg(ptr, int);
                    int base = va_arg(ptr, int);
                    //string = cc10_to_base_cc_upper(number, base, &want_write_amount);
                    break;
                }



            }

            //add_to_buffer(&buffer, &size_buf, &written, &want_write_amount, string);

            position += 3;
            //free(string);
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


    amount += vfscanf(stream, buffer, ptr);

    va_end(ptr);
    free(buffer);
    return amount;
}
