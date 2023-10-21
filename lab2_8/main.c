#include "helper.h"



int main() {
    memory stat = msc_well;
    int base = 17;
    char* first = "G";
    char* second = "Ag";
    char* third = "B";
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
