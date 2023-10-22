#include "helper.h"

int my_strlen(const char* string)
{
    int length = 0;
    while(string[length] != '\0')
    {
        length++;
    }

    return length;
}


int my_strcmp(const char* first, const char* second)
{
    int len1 = my_strlen(first);
    int len2 = my_strlen(second);

    int i = 0;
    while(first[i] != '\0' || second[i] != '\0')
    {
        if(first[i] != second[i])
        {
            if(len1 - len2 == 0){
                return -1;
            }
            return len1 - len2;
        }
        i++;
    }
    return 0;
}

input analysis(int argc, char** argv){
    char act = '0';
    if(argc < 3)
    {
        return isc_bad_input;
    }
    if(argc == 3 || argc >= 4)
    {
        if(!my_strcmp(argv[1], "-l") || !my_strcmp(argv[1], "-r") || !my_strcmp(argv[1], "-u") ||!my_strcmp(argv[1], "-n") ||!my_strcmp(argv[1], "-c")){
            act = argv[1][1];
        }else{
            return isc_bad_input;
        }

    }

    if(act == 'l' && argc == 3){
        return isc_l;
    }
    if(act == 'r' && argc == 3){
        return isc_r;
    }
    if(act == 'u' && argc == 3){
        return isc_u;
    }
    if(act == 'n' && argc == 3){
        return isc_n;
    }
    if(act == 'c' && argc >= 4){
        return isc_c;
    }

    return isc_bad_input;
}

char* reverse_string(char* str)
{
    int length = my_strlen(str) ;
    char* new_str = (char*)malloc(sizeof(char)*(length+1));
    if(new_str == NULL){
        return NULL;//enum-чик
    }

    int i = 0;
    int j = 0;

    for (i = length - 1, j = 0; i > 0, j < length; i--, j++)
    {
        new_str[j] = str[i];
    }
    new_str[length] = '\0';

    return new_str;
}

char* up_half_string(char* str){
    int length = my_strlen(str);
    char* new_str = (char*)malloc(sizeof(char)*(length+1));
    if(new_str == NULL){
        return NULL;//enum
    }
    for(int i = 0; i < length; ++i){
        new_str[i] = str[i];
    }
    new_str[length] = '\0';
    for(int i = 1; i < length; i += 2){
        new_str[i] = toupper(new_str[i]);
    }
    return new_str;
}

char* ordered_string(char* str){
    int length = my_strlen(str);
    char* new_str = (char*)malloc(sizeof(char)*(length+1));
    if(new_str == NULL){
        return NULL;//enum
    }
    int count = 0;
    for(int i = 0; i < length; ++i){
        if(isdigit(str[i])){
            new_str[count++] = str[i];
        }
    }
    for(int i = 0; i < length; ++i){
        if(isalpha(str[i])){
            new_str[count++] = str[i];
        }
    }
    for(int i = 0; i < length; ++i){
        if(!isdigit(str[i]) && !isalpha(str[i])){
            new_str[count++] = str[i];
        }
    }
    new_str[length] = '\0';

    return new_str;


}

uint arg_to_ud(char* str, unsigned int* answer){
    *answer = 0;
    int i = 0;
    while(str[i] != '\0'){
        if(isdigit(str[i]))
        {
            if(*answer > ((unsigned int)-1)/10){
                return usc_overflow;
            }
            *answer = *answer*10 + (str[i] - '0');
        }else{
            return usc_bad_number;
        }
        i++;
    }
    return usc_well;
}




int random_number(int min, int max){
    return min + rand() % (max - min +1);
}

void string_permutations(char** strs, int size){
    for(int i = 0; i < size; ++i){
        int random = random_number(0, i);
        char* tmp = strs[i];
        strs[i] = strs[random];
        strs[random] = tmp;
    }
}

char* concatenation(char** strs, int count){
    int full_size = 0;
    for(int i = 0; i < count; ++i){
        full_size += my_strlen(strs[i]);
    }

    char* conclusion = (char*)malloc(sizeof(char) * (full_size+1));
    if(conclusion == NULL){
        return NULL;//enum
    }

    int counter = 0;
    for(int i = 0; i < count; ++i){
        int local_len = my_strlen(strs[i]);
        for(int j = 0; j < local_len; ++j){
            conclusion[counter++] = strs[i][j];
        }
    }
    conclusion[full_size] = '\0';
    return conclusion;

}
