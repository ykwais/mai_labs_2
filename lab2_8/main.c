#include "helper.h"



int main() {
    memory stat = msc_well;
    int base = 36;
    char* first = "z";
    char* second = "z";
    char* third = "z";
    char* result = adding(&stat,base, 3, first, second, third);
    if(stat == msc_problem){
        printf("Problems with memory allocation!\n");
        return 0;
    }else{
        result = delete_zeros(result);
        printf("\n%s\n", result);
        free(result);
    }

}
