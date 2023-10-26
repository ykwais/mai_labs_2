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
                    int arg = va_arg(ptr, int);
                    string = int_to_rom(arg, &want_write_amount);
                    break;
                }

                case Zr:{
                    unsigned int arg = va_arg(ptr, unsigned int);
                    string = zeck(arg, &want_write_amount);
                    break;
                }
                case Cv: {
                    int number = va_arg(ptr, int);
                    int base = va_arg(ptr, int);
                    string = cc10_to_base_cc_lower(number, base, &want_write_amount);
                    break;
                }


                case CV:{
                    int number = va_arg(ptr, int);
                    int base = va_arg(ptr, int);
                    string = cc10_to_base_cc_upper(number, base, &want_write_amount);
                    break;
                }


                case to:{
                    char* str = va_arg(ptr, char*);
                    int base = va_arg(ptr, int);
                    string = string_cc_to_10CC_lower(str, base, &want_write_amount);
                }

                    break;
                case TO:{
                    char* str = va_arg(ptr, char*);
                    int base = va_arg(ptr, int);
                    string = string_cc_to_10CC_upper(str, base, &want_write_amount);
                }

                    break;
                case mi:{
                    int arg = va_arg(ptr, int);
                    string = dump(&arg, sizeof(int), &want_write_amount);
                }



                    break;
                case mu:{
                    unsigned int arg = va_arg(ptr, unsigned int);
                    string = dump(&arg, sizeof(unsigned int), &want_write_amount);
                }


                    break;
                case md:{
                    double arg = va_arg(ptr, double);
                    string = dump(&arg, sizeof(double), &want_write_amount);
                }



                    break;
                case mf:{
                    float arg = va_arg(ptr, double );
                    string = dump(&arg, sizeof(float), &want_write_amount);
                }


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


char* cc10_to_base_cc_lower(int num, int base, int* amount)
{
    char* tmp = NULL;
    if(base > 36 || base < 2){
        base = 10;
    }

    int size = 2;
    int count = 0;
    int start = 0;

    char* result = (char*)malloc(sizeof(char)*(size));
    if(result == NULL){
        return NULL; // mem bad alloc
    }


    int r;
    if (num < 0) {
        result[count] = '-';
        count++;
        start = 1;
        num *= -1;
    }


    while (num > 0) {
        r = num % base;
        if(count >= size){
            size *= 2;
            if(!(tmp = (char*) realloc(result, size))){
                free(result);
                return NULL;//mem alloc problem
            }
            result = tmp;
        }
        result[count] = (r > 9) ? r - 10 + 'a' : r + 48;
        count++;
        num /= base;
    }
    for (int i = start, j = count - 1; i < j; i++, j--)
    {
        char tmp  = result[i];
        result[i] = result[j];
        result[j] = tmp;
    }
    result[count] = '\0';
    *amount = count;
    return result;
}


char* cc10_to_base_cc_upper(ll num, int base, int* amount)
{
    char* tmp = NULL;
    if(base > 36 || base < 2){
        base = 10;
    }

    int size = 2;
    int count = 0;
    int start = 0;

    char* result = (char*)malloc(sizeof(char)*(size));
    if(result == NULL){
        return NULL; // mem bad alloc
    }


    int r;
    if (num < 0) {
        result[count] = '-';
        count++;
        start = 1;
        num *= -1;
    }


    while (num > 0) {
        r = num % base;
        if(count >= size){
            size *= 2;
            if(!(tmp = (char*) realloc(result, size))){
                free(result);
                return NULL;//mem alloc problem
            }
            result = tmp;
        }
        result[count] = (r > 9) ? r - 10 + 'A' : r + 48;
        count++;
        num /= base;
    }
    for (int i = start, j = count - 1; i < j; i++, j--)
    {
        char tmp  = result[i];
        result[i] = result[j];
        result[j] = tmp;
    }
    result[count] = '\0';
    *amount = count;
    return result;
}

bool is_lower_alpha(char c){
    return (c >= 97 && c <= 122);
}

bool is_upper_alpha(char c){
    return (c >= 65 && c <= 90);
}


int length_long_long(long long number){
    char random_string[20];
    sprintf(random_string, "%lld",number);

    return (int)strlen(random_string);
}

char* string_cc_to_10CC_lower(char *string, int base, int* amount) {//здесь буду отслеживать переполнение
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
                char* answer = cc10_to_base_cc_upper(result, 10, amount);
                return answer;
            }
            result = result * base + (isdigit(*ptr) ? *ptr - '0' : *ptr - 'a' + 10);
            ptr++;
            count++;
        }
        else{
            char* answer = cc10_to_base_cc_upper(result, 10, amount);
            return answer;
        }

    }

    if(negative)
    {
        result *= -1;
    }

    char* answer = cc10_to_base_cc_upper(result, 10, amount);
    return answer;

}


char* string_cc_to_10CC_upper(char *string, int base, int* amount) {//здесь буду отслеживать переполнение
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
                char* answer = cc10_to_base_cc_upper(result, 10, amount);
                return answer;
            }
            result = result * base + (isdigit(*ptr) ? *ptr - '0' : *ptr - 'A' + 10);
            ptr++;
            count++;
        }
        else{
            char* answer = cc10_to_base_cc_upper(result, 10, amount);
            return answer;
        }

    }

    if(negative)
    {
        result *= -1;
    }

    char* answer = cc10_to_base_cc_upper(result, 10, amount);
    return answer;

}

char* dump(const void *value, int size_of, int* amount)
{
    const unsigned char *bytes = (const unsigned char *)value;

    int buffer_size =  size_of * 9;
    int written = 0;
    char* res = (char *) malloc(sizeof(char)*buffer_size);
    if(res == NULL){
        return NULL;//mem alloc problem
    }

    for (int i = size_of-1; i >=0; i--)
    {
        for (int bit = 7; bit >= 0; bit--)
        {
            int bit_value = (bytes[i] >> bit) & 1;
            written += sprintf(res + written,  "%d", bit_value);
        }
        written += sprintf(res + written,  "%c", ' ');
    }
    *amount = written;
    return res;
}




































