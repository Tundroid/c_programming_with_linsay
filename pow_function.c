#include <stdio.h>

int my_pow(int base, int exp)
{
    if (exp == 0)
    {
        return 1;
    } else if (exp == 1)
    {
        return base;
    }
    else
    {
        int result = base;

        for (int i = 1; i < exp; i++)
        {
            result *= base;
        }

        return result;
    }
}

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