#include "helper.h"

int howmuch(char* str, int count)
{
    int answer = 0;
    for(int i = 0; i < count; ++i){
        while(!isspace(str[answer])){
            ++answer;
        }
        while(isspace(str[answer])){
            ++answer;
        }

    }
    return answer;
}

not_my_flag another_flag(char* string, int* amount)
{
    if(string[0] == '%' && string[1] == 'c' ){
        *amount = 2;
        return CHAR;
    }
    if(string[0] == '%' && string[1] == 's' ){
        *amount = 2;
        return STRING;
    }
    if(string[0] == '%' && (string[1] == 'i' || string[1] == 'd' || string[1] == 'x' || string[1] == 'X' || string[1] == 'o')){
        *amount = 2;
        return INT;
    }
    if(string[0] == '%' && string[1] == 'f' ){
        *amount = 2;
        return DOUB;

    }
    if(string[0] == '%' && string[1] == 'l' && string[2] == 'f'){
        *amount = 3;
        return DOUB;
    }
    if(string[0] == '%' && string[1] == 'L' && string[2] == 'F' ){
        *amount = 3;
        return LD;
    }
    if(string[0] == '%' && string[1] == 'l' && string[2] == 'd'  ){
        *amount = 3;
        return LI;
    }
    if(string[0] == '%' && string[1] == 'l' && string[2] == 'l' && string[3] == 'd'){
        *amount = 4;
        return LL;
    }

    if(string[0] == '%' && string[1] == 'p' ){
        *amount = 2;
        return POINTER;
    }

    return un;
};


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



bool is_lower_alpha(char c)
{
    return (c >= 97 && c <= 122);
}

bool is_upper_alpha(char c)
{
    return (c >= 65 && c <= 90);
}

int length_long_long(long long number)
{
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

ll string_cc_to_10CC_upper(char *string, int base, int* amount) {//здесь буду отслеживать переполнение
    if(base > 36 || base < 2){
        base = 10;
    }
    bool negative = false;
    char *ptr = string;
    long long result = 0;
    int count = 0;

    while (*ptr) {
        if(isdigit(*ptr) || is_upper_alpha(*ptr) || (*ptr == 45 && count == 0)){
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
            result = result * base + (isdigit(*ptr) ? *ptr - '0' : *ptr - 'A' + 10);
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


int roman_to_int(char* str) {
    int result = 0;
    int previous = 0;


    int values[7] = {1000, 500, 100, 50, 10, 5, 1};
    char symbols[7] = {'M', 'D', 'C', 'L', 'X', 'V', 'I'};

    int length = strlen(str);


    for (int i = length-1; i >= 0; i--) {

        int index = 0;
        while (symbols[index] != str[i]) {
            index++;
        }


        if (symbols[index + 1] != '\0' && values[index] < previous) {
            result -= values[index];//IV, IX ...
        }

        else {
            result+= values[index];
        }
        previous = values[index];
    }

    return result;
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

    while (counter < max)
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


int zeck_to_int(char* str)
{
    int result = 0;
    int n = 0;
    int length = strlen(str);
    unsigned int* fibs = fib_row(length-1, &n);
    for(int i = 0; i < length-1; i++){
        if(str[i] == '1'){
            result += fibs[i];
        }
    }
    free(fibs);
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
    if(buffer == NULL){
        return 0;//bad  mem alloc
    }
    buffer[0] = '\0';

    flag current_flag = u;
    not_my_flag extra_flag = un;

    va_list ptr;
    va_start(ptr, format);


    while(format[position] != '\0' && position < length){
        if(extra_flag != un){
            buffer[written] = '\0';
            amount += vfscanf(stream, buffer, ptr);

            switch(extra_flag){
                case CHAR:{
                    va_arg(ptr, int);
                    break;
                }
                case STRING:{
                    va_arg(ptr, char*);
                    break;
                }
                case INT:{
                    va_arg(ptr, int);
                    break;
                }
                case DOUB:{
                    va_arg(ptr, double);
                    break;
                }
                case LD:{
                    va_arg(ptr, long double);
                    break;
                }
                case LL:{
                    va_arg(ptr, long long int);
                    break;
                }
                case LI:{
                    va_arg(ptr, long int);
                    break;
                }
                case POINTER:{
                    va_arg(ptr, char*);
                }
            }

            buffer[0] = '\0';
            written = 0;
            size_buf = 1;
            extra_flag = un;
        }

        if(format[position] == '%' && (current_flag = type_flag(format+position))!=not_my){

            buffer[written] = '\0';
            amount += vfscanf(stream, buffer, ptr);

            switch(extra_flag){
                case CHAR:{
                    va_arg(ptr, int);

                }
                    break;
                case STRING:{
                    va_arg(ptr, char*);

                }
                    break;
                case INT:{
                    va_arg(ptr, int);

                }
                    break;
                case DOUB:{
                    va_arg(ptr, double);

                }
                    break;
                case LD:{
                    va_arg(ptr, long double);

                }
                    break;
                case LL:{
                    va_arg(ptr, long long int);

                }
                    break;
                case LI:{
                    va_arg(ptr, long int);

                }
                    break;
                case POINTER:{
                    va_arg(ptr, char*);
                }
                    break;
            }

            buffer[0] = '\0';
            written = 0;
            size_buf = 1;
            extra_flag = un;



            switch(current_flag){
                case Ro: {
                    int* number = va_arg(ptr, int*);
                    char tmp[100];
                    fscanf(stream, "%s", tmp);
                    *number = roman_to_int(tmp);
                    amount++;
                    break;
                }

                case Zr:{
                    int* number = va_arg(ptr, int*);
                    char tmp[100];
                    fscanf(stream, "%s", tmp);
                    *number = zeck_to_int(tmp);
                    amount++;

                    break;
                }
                case Cv: {
                    int* number = va_arg(ptr, int*);
                    int base = va_arg(ptr, int);
                    //printf("base inputted: %d\n", base);
                    char tmp[65];
                    fscanf(stream, "%s", tmp);
                    *number = string_cc_to_10CC_lower(tmp, base, &want_write_amount);
                    amount++;
                    break;
                }


                case CV:{
                    int* number = va_arg(ptr, int*);
                    int base = va_arg(ptr, int);
                    //printf("base inputted: %d\n", base);
                    char tmp[65];
                    fscanf(stream, "%s", tmp);
                    *number = string_cc_to_10CC_upper(tmp, base, &want_write_amount);
                    amount++;
                    break;
                }

            }

            position += 3;
            current_flag = u;

            continue;

        }
        else{
            if(current_flag == not_my && format[position] == '%'){
                extra_flag = another_flag(format + position, &want_write_amount);
                if(extra_flag == un){
                    return 0;//неопознанный
                }
                add_to_buffer(&buffer, &size_buf, &written, &want_write_amount, format + position);
                position += want_write_amount;

                continue;
            }

            want_write_amount = 1;
            add_to_buffer_1(&buffer, &size_buf, &written, &want_write_amount, format[position]);

            position++;
            current_flag = u;

        }
        current_flag = u;

    }

    if(extra_flag != un){
        buffer[written] = '\0';
        amount += vfscanf(stream, buffer, ptr);

        switch(extra_flag){
            case CHAR:{
                va_arg(ptr, int);
                break;
            }
            case STRING:{
                va_arg(ptr, char*);
                break;
            }
            case INT:{
                va_arg(ptr, int);
                break;
            }
            case DOUB:{
                va_arg(ptr, double);
                break;
            }
            case LD:{
                va_arg(ptr, long double);
                break;
            }
            case LL:{
                va_arg(ptr, long long int);
                break;
            }
            case LI:{
                va_arg(ptr, long int);
                break;
            }
            case POINTER:{
                va_arg(ptr, char*);
            }
        }

        buffer[0] = '\0';
        written = 0;
        size_buf = 1;
        extra_flag = un;
    }

    buffer[written] = '\0';


    amount += vfscanf(stream, buffer, ptr);

    va_end(ptr);
    free(buffer);
    return amount;
}


int oversscanf(char* str, char* format, ...)
{
    int bl = 0;

    int amount = 0;

    int length = strlen(format);

    int position = 0;

    int written = 0;

    int size_buf = 1;

    int how_m = 0;

    int want_write_amount = 0;

    char* buffer = (char*)malloc(sizeof(char)*(size_buf));
    if(buffer == NULL){
        return 0;//bad  mem alloc
    }
    buffer[0] = '\0';

    flag current_flag = u;
    not_my_flag extra_flag = un;

    va_list ptr;
    va_start(ptr, format);


    while(format[position] != '\0' && position < length){
        if(extra_flag != un){
            buffer[written] = '\0';
            amount += vsscanf(str+how_m, buffer, ptr);
            how_m = howmuch(str, amount);

            switch(extra_flag){
                case CHAR:{
                    va_arg(ptr, int);
                    break;
                }
                case STRING:{
                    va_arg(ptr, char*);
                    break;
                }
                case INT:{
                    va_arg(ptr, int);
                    break;
                }
                case DOUB:{
                    va_arg(ptr, double);
                    break;
                }
                case LD:{
                    va_arg(ptr, long double);
                    break;
                }
                case LL:{
                    va_arg(ptr, long long int);
                    break;
                }
                case LI:{
                    va_arg(ptr, long int);
                    break;
                }
                case POINTER:{
                    va_arg(ptr, char*);
                }
            }

            buffer[0] = '\0';
            written = 0;
            size_buf = 1;
            extra_flag = un;
        }

        if(format[position] == '%' && (current_flag = type_flag(format+position))!=not_my){

            buffer[written] = '\0';
            amount += vsscanf(str + how_m, buffer, ptr);
            how_m = howmuch(str, amount);

            switch(extra_flag){
                case CHAR:{
                    va_arg(ptr, int);

                }
                    break;
                case STRING:{
                    va_arg(ptr, char*);

                }
                    break;
                case INT:{
                    va_arg(ptr, int);

                }
                    break;
                case DOUB:{
                    va_arg(ptr, double);

                }
                    break;
                case LD:{
                    va_arg(ptr, long double);

                }
                    break;
                case LL:{
                    va_arg(ptr, long long int);

                }
                    break;
                case LI:{
                    va_arg(ptr, long int);

                }
                    break;
                case POINTER:{
                    va_arg(ptr, char*);
                }
                    break;
            }

            buffer[0] = '\0';
            written = 0;
            size_buf = 1;
            extra_flag = un;



            switch(current_flag){
                case Ro: {
                    int* number = va_arg(ptr, int*);
                    char tmp[100];
                    sscanf(str + how_m, "%s", tmp);
                    *number = roman_to_int(tmp);
                    amount++;
                    break;
                }

                case Zr:{
                    int* number = va_arg(ptr, int*);
                    char tmp[100];
                    sscanf(str+ how_m, "%s", tmp);
                    *number = zeck_to_int(tmp);
                    amount++;

                    break;
                }
                case Cv: {
                    int* number = va_arg(ptr, int*);
                    int base = va_arg(ptr, int);
                    //printf("base inputted: %d\n", base);
                    char tmp[65];
                    sscanf(str+ how_m, "%s", tmp);
                    *number = string_cc_to_10CC_lower(tmp, base, &want_write_amount);
                    amount++;
                    break;
                }


                case CV:{
                    int* number = va_arg(ptr, int*);
                    int base = va_arg(ptr, int);
                    //printf("base inputted: %d\n", base);
                    char tmp[65];
                    sscanf(str+ how_m, "%s", tmp);
                    *number = string_cc_to_10CC_upper(tmp, base, &want_write_amount);
                    amount++;
                    break;
                }

            }
            how_m = howmuch(str, amount);
            position += 3;
            current_flag = u;

            continue;

        }
        else{
            if(current_flag == not_my && format[position] == '%'){
                extra_flag = another_flag(format + position, &want_write_amount);
                if(extra_flag == un){
                    return 0;//неопознанный
                }
                add_to_buffer(&buffer, &size_buf, &written, &want_write_amount, format + position);
                position += want_write_amount;

                continue;
            }

            want_write_amount = 1;
            add_to_buffer_1(&buffer, &size_buf, &written, &want_write_amount, format[position]);

            position++;
            current_flag = u;

        }
        current_flag = u;

    }

    if(extra_flag != un){
        buffer[written] = '\0';
        amount += vsscanf(str + how_m, buffer, ptr);
        how_m = howmuch(str, amount);

        switch(extra_flag){
            case CHAR:{
                va_arg(ptr, int);
                break;
            }
            case STRING:{
                va_arg(ptr, char*);
                break;
            }
            case INT:{
                va_arg(ptr, int);
                break;
            }
            case DOUB:{
                va_arg(ptr, double);
                break;
            }
            case LD:{
                va_arg(ptr, long double);
                break;
            }
            case LL:{
                va_arg(ptr, long long int);
                break;
            }
            case LI:{
                va_arg(ptr, long int);
                break;
            }
            case POINTER:{
                va_arg(ptr, char*);
            }
        }

        buffer[0] = '\0';
        written = 0;
        size_buf = 1;
        extra_flag = un;
    }

    buffer[written] = '\0';


    amount += vsscanf(str+how_m, buffer, ptr);
    //how_m = howmuch(str, amount);
    va_end(ptr);
    free(buffer);
    return amount;
}
