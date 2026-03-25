#include <stdio.h>

int main()
{
    int a;
    printf("Enter integer to check if it is prime: ");
    scanf("%i", &a);

    int count = 0;

    if (a == 1)
    {
        count = 2;
    }
    else
    {
        for (int i = 1; i <= a; i++)
        {
            if (a % i == 0)
            {
                count++;
            }
        }
    }

    if (count == 2)
    {
        printf("%d is a prime number", a);
    }
    else
    {
        printf("%d is not a prime number", a);
    }
}