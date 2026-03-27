#include <math.h>

int my_pow(int base, int exp)
{
    if (exp == 0)
    {
        return 1;
    }
    else if (exp == 1)
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

int square(int x)
{
    return my_pow(x, 2);
}

int cube(int x)
{
    return my_pow(x, 3);
}

// TODO: fix this function, it only works for perfect squares
int my_sqrt(int x)
{
    for (int i = 0; i < x; i++)
    {
        if (square(i) == x)
        {
            return i;
        }
    }

    return -1;
}

int factorial(int x)
{
    if (x == 0 || x == 1)
    {
        return 1;
    }
    else
    {
        int result = 1;
        for (int i = 2; i <= x; i++)
        {
            result *= i;
        }

        return result;
    }
}

int my_abs(int x)
{
    if (x < 0)
    {
        return x * -1;
    }
    else
    {
        return x;
    }
}

// TODO: fix this function, it only works for base 10
int my_log(int base, int x)
{
    if (base <= 1 || x <= 0)
    {
        return -1; // Logarithm is not defined for base <= 1 or x <= 0
    }
    else if (base == x)
    {
        return 1; // log_b(b) = 1
    }
    else if (x == 1)
    {
        return 0; // log_b(1) = 0
    }

    int result = 0;
    int power_of_10 = 1;

    while (power_of_10 <= x)
    {
        power_of_10 *= 10;
        result++;
    }

    return result - 1; // Subtract 1 to get the correct logarithm value
}

void my_quadratic_solver(int a, int b, int c, double *root1, double *root2)
{
    int discriminant = square(b) - 4 * a * c;

    if (discriminant == 0)
    {
        *root1 = -b / (2 * a);
        *root2 = *root1;
    }
    else if (discriminant > 0)
    {
        *root1 = (-b + sqrt(discriminant)) / (2 * a);
        *root2 = (-b - sqrt(discriminant)) / (2 * a);
    }
    else
    {
        *root1 = -1; // Indicate no real roots
        *root2 = -1;
    }
}