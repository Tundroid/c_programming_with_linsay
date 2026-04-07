/**
 * This program prints money with a dollar sign and two decimal places and padded with # to a width of 10 characters.
 * The output is right-aligned.
 */

#include <stdio.h>
int main()
{
    double money;

    printf("Enter the amount of money: ");
    scanf("%lf", &money);

    printf("Formatted right-align money: %10.2lf|\n", money);
    printf("Formatted left-align money: %-10.2lf|\n", money);

    return 0;
}