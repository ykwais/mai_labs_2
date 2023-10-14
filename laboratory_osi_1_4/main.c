#include <stdio.h>
#include "enums.h"
#include "funcs.c"


int main(int argc, char **argv) {
    int answer = 0;
    char result[4] = {0, 0, 0, 0};
    int counter = 0;

    file_troubles stat;
    memory mem_status;
    valid_mask mask_status;
    char* mask;

    switch (analysis(argc, argv)) {

        case isc_too_args:
            printf("You've inputted too many/little arguments");
            break;
        case isc_bad_input:
            printf("Bad input, sorry.");
            break;
        case isc_xor8:
            xor_8(argv[2], &answer, &stat);
            if(stat == ofp_bad_open)
            {
                printf("Bad opening the file!");
                return 0;
            }
            printf("answer for xor_2 = %d\n", answer);
            break;
        case isc_xor32:
            xor_32(argv[2], result, &stat);
            if(stat == ofp_bad_open)
            {
                printf("Bad opening the file!");
                return 0;
            }
            printf("answer for xor_32 : \n");
            for (int i = 0; i < 4; ++i)
            {
                printf("%d ", result[i]);
            }
            break;
        case isc_mask:
            mask = get_mask(argv[3], &mem_status, &mask_status);

            if(mem_status == mt_memory_problem){
                printf("There are problems with a memory allocation!");
                return 0;
            }
            mask_func(argv[2], &counter, mask, &stat);
            if(stat == ofp_bad_open)
            {
                printf("Bad opening the file!");
                return 0;
            }
            if(mask_status == vvm_invalid)
            {
                printf("\nall invalid mask values have been replaced with 0\n");
            }
            printf("\nresult of mask : %d\n", counter);
            break;
    }


}
