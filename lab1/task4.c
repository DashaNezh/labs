#include <stdio.h>

int main(void){
    int a,b,c,x;
    printf("input a:\n");
    scanf("%d",&a);
    printf("input b:\n");
    scanf("%d",&b);
    printf("input c:\n");
    scanf("%d",&c);
    x = (c-b)/a;
    printf("x = %.2f\n",x);
    return 0;
}