#include <stdio.h>

int checkPrime(int x)
{
    if (x == 1 || x == 2)
    {
        return 1;
    }
    else if (x % 2 == 0)
    {
        return 0;
    }
    else
    {
        for (int i = 3; i < x / 2; i++)
        {
            if (x % i == 0)
            {
                return 0;
            }
        }

        return 1;
    }
}

int main()
{
    int a;

    printf("Enter integer to check if it is prime: ");
    scanf("%i", &a);

    if (checkPrime(a) == 1)
    {
        printf("%d is a prime number", a);
    }
    else
    {
        printf("%d is not a prime number", a);
    }

    return 0;
}