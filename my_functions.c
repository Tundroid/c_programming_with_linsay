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