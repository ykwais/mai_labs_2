

#include "helper.h"




int main() {
    switch (is_convex(0.0000000001L, 4, (point){1,1},(point){3,2}, (point){3,4}, (point){1,4}  )) {
        case osc_no:
            printf("\nno\n\n");
            break;
        case osc_yes:
            printf("\nyes\n\n");
            break;
    }


    printf("%Lf\n", polynom(2, 4, (ld)1,(ld)6, (ld)-8.43, (ld)-17.33, (ld)1));

}
