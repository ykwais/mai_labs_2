#include "helper.h"

int main() {
    int d = 0;
    int k = 0;
    int g = 0;
    int num = 0;
    int base = 10;
    long long alpha = 0;
    char str[10];
    char c;
    int roman = 0;
    int zeckenorf = 0;

//    int l = roman_to_int("MMMCDLIX");
//    printf("%d\n", l);



    overfscanf(stdin, "%c%Zr%d%s %Cv%d%lld %CV%Ro", &c, &zeckenorf,&num, &str, &k, 16, &g, &alpha, &d, 16, &roman);



    printf("%c\n", c);
    printf("zeck: %d\n", zeckenorf);
    printf("%d\n", num);
    printf("%s\n", str);
    printf("%d\n", k);
    printf("%d\n", g);
    printf("%lld\n", alpha);
    printf("%d\n", d);
    printf("roman: %d\n", roman);


    printf("here:\n");
    fflush(stdin);

    overfscanf(stdin, "%s", &str);
    printf("%s\n",str);

    oversscanf("T 0010010011 234 sdf a9 -587 2435 A9 MMM", "%c%Zr%d%s %Cv%d%lld %CV%Ro", &c, &zeckenorf,&num, &str, &k, 16, &g, &alpha, &d, 16, &roman);
    printf("!!!\n");
    printf("%c\n", c);
    printf("zeck: %d\n", zeckenorf);
    printf("%d\n", num);
    printf("%s\n", str);
    printf("%d\n", k);
    printf("%d\n", g);
    printf("%lld\n", alpha);
    printf("%d\n", d);
    printf("roman: %d\n", roman);




    //printf("%d\n", d);
}


