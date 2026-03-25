#include <stdio.h>
#include "my_functions.c"


int main()
{
    int base, exp;

    printf("Enter base: ");
    scanf("%i", &base);

    printf("Enter exponent: ");
    scanf("%i", &exp);

    printf("%d^%d = %d", base, exp, my_pow(base, exp));

    return 0;
}