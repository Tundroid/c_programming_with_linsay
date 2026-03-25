#include <stdio.h>
void multiply_numbers(int num1, int num2)
{
    int multiply = num1 * num2;
    printf("The product is: %d and %d is %d", num1, num2, multiply);
}
int main()
{
    printf("Enter two numbers: ");
    int num1, num2;
    scanf("%d %d", &num1, &num2);
    multiply_numbers(num1, num2);

    return 0;
}
