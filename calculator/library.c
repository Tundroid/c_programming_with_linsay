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
int my_log(int x)
{
    if (x <= 0)
    {
        return -1; // Logarithm is not defined for negative numbers
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
int quadradic_formula(int a, int b, int c, int root1, int root2)
{
    int discriminant = square(b) - 4 * a * c;

    if (discriminant == 0)  
    {
        root1 = -b / (2 * a);
        root2 = root1;
    }
    else if (discriminant > 0)
    {
        root1 = (-b + my_sqrt(discriminant)) / (2 * a);
        root2 = (-b - my_sqrt(discriminant)) / (2 * a);
    }
}