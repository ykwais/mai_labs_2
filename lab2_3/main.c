
#include "helper.h"




int main() {
    int count_of_file = 2;
    int count_matches = 0;
    one_file* result_info = (one_file*) malloc(sizeof(one_file));
    if(result_info == NULL){
        printf("no mem\n");
        return 0;
    }

   switch(pattern_search(&result_info, "abc\n\n",&count_matches, count_of_file, "file1.txt","file2.txt")){
        case all_well:
            for(int i = 0; i < count_matches; ++i){
                printf("in file: %s\n", result_info[i].filename);
                printf("number string: %d\n", result_info[i].strok_number);
                printf("number symbol: %d\n", result_info[i].symbol_number);
                printf("\n");
            }
           break;
        case fseek_problem:
            printf("problem with fseek\n");
           break;
        case file_problem:
            printf("problem with file opening\n");
            break;
       case mem_problem:
           printf("Problem with memory allocation\n");
           break;
        case null_pattern:
            printf("as you've entered null-pattern, anything will do\n");
           break;
    }



    free(result_info);
}
