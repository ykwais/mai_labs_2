#include "helper.h"



int main() {
    memory stat = msc_well;
    int base = 36;
    char* first = "A";
    char* second = "A";
    char* third = "B";
    char* result = adding(&stat,base, 2, first, second);
    if(stat == msc_problem){
        printf("Problems with memory allocation!\n");
        return 0;
    }else{
        result = delete_zeros(result);
        printf("\n%s\n", result);
        free(result);
    }

}
