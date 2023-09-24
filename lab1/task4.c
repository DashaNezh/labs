#include <stdio.h>

int main(void){
    float a,b,c,x;
    printf("input a:\n");
    scanf("%f",&a);
    printf("input b:\n");
    scanf("%f",&b);
    printf("input c:\n");
    scanf("%f",&c);
    x = (c-b)/a;
    printf("x = %.2f\n",x);
    return 0;
}
