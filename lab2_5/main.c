#include "helper.h"




int main() {

    FILE* file = NULL;
    if(!(file = fopen("out.txt", "w"))){
        printf("trouble opening the file\n");
        return 0;
    }

    int c;
    //printf("%d\n",overfprintf(stdout, "sj%dk%CV%TOdf%Ro%x\n\0hg", 13));
    overfprintf(stdout, "sj%dsdf%Ro%lld^^^^hggf%%%Ro%%%%Zrj%Cvkjhgdcfglkjhdvclkjhvfdvlkjhgfdglkj%CV\n%todfghjdhgfj\n%TO\n%mi\n%mu\n%md\n%mf", 10, 54, 5000, 6, 6, -35,36, -45, 16, "abc",11 ,"ABC",11, -31, -31, -78.9, 78.9);
    c = overfprintf(file, "sdafhd %TO ^^^dfljk", "10", 2);

    printf("\n\n\n%d\n\n\n", c);

    fclose(file);

    char* str = NULL;
    oversprintf(&str,"\n\nshjdfgb%dfhj#%s#kg %Ro df  %Zr  %Cv", 10,"dfd",10, 89, 35,36);
    printf("\n%s", str);

    oversprintf(&str, "23",12);
    printf("\n%s", str);
    free(str);
}

