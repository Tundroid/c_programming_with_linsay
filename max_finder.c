#include <stdio.h>

int main(){
    int a, b, max;

    printf("Enter first number: ");
    scanf("%d", &a);
    printf("Enter second number: ");
    scanf("%d", &b);

    if (a > b){
        max = a;
    } else {
        max = b;
    }

    printf("Max between %d and %d is %d!", a, b, max);

    return 0;
}