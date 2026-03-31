#include <stdio.h>
#include "library.c"

int readInt(const char *prompt)
{
	int value;

	while (1)
	{
		int scanCount;

		printf("%s", prompt);
		scanCount = scanf("%d", &value);

		if (scanCount == 1)
		{
			return value;
		}

		printf("Invalid input. Please enter an integer.\n");
		while (getchar() != '\n')
		{
		}
	}
}

void printBanner(void)
{
	printf("\n");
	printf("+------------------------------------------+\n");
	printf("|         LINSAY'S FANCY CALCULATOR       |\n");
	printf("+------------------------------------------+\n");
	printf("| 1. Power (base^exp)                      |\n");
	printf("| 2. Square                                |\n");
	printf("| 3. Cube                                  |\n");
	printf("| 4. Integer square root                   |\n");
	printf("| 5. Factorial                             |\n");
	printf("| 6. Absolute value                        |\n");
	printf("| 7. Logarithm                             |\n");
	printf("| 8. Quadratic Solver                      |\n");
	printf("| 9. Exit                                  |\n");
	printf("+------------------------------------------+\n");
}

void printResultLine(void)
{
	printf("--------------------------------------------\n");
}

int main(void)
{
	int option;


	while (1)
	{
		int n;
		int answer;

		printBanner();
		option = readInt("Select an option (1-9): ");

		if (option == 9)
		{
			printf("\nThanks for using Linsay's Fancy Calculator. Bye!\n");
			break;
		}

		printResultLine();

		switch (option)c
		{
		case 1:
		{
			int base = readInt("Enter base: ");
			int exp = readInt("Enter exponent (>= 0): ");

			if (exp < 0)
			{
				printf("Negative exponents are not supported by this integer power function.\n");
			}
			else
			{
				answer = my_pow(base, exp);
				printf("Result: %d^%d = %d\n", base, exp, answer);
			}
			break;
		}

		case 2:
		{
			n = readInt("Enter number: ");
			answer = square(n);
			printf("Result: square(%d) = %d\n", n, answer);
			break;
		}

		case 3:
		{
			n = readInt("Enter number: ");
			answer = cube(n);
			printf("Result: cube(%d) = %d\n", n, answer);
			break;
		}
		case 4:
			n = readInt("Enter non-negative number: ");
			if (n < 0)
			{
				printf("Square root for negative numbers is not supported here.\n");
			}
			else
			{
				answer = my_sqrt(n);
				if (answer == -1)
				{
					printf("%d is not a perfect square.\n", n);
				}
				else
				{
					printf("Result: sqrt(%d) = %d\n", n, answer);
				}
			}
			break;

		case 5:
		{
			n = readInt("Enter non-negative integer: ");
			if (n < 0)
			{
				printf("Factorial is not defined for negative integers.\n");
			}
			else
			{
				answer = factorial(n);
				printf("Result: %d! = %d\n", n, answer);
			}
			break;
		}
		case 6:
		{
			int base;
			n = readInt("Enter number: ");
			answer = my_abs(n);
			printf("Result: abs(%d) = %d\n", n, answer);
			break;
		}
		case 7:
		{
			int base, x;
			double result;
			printf("Enter base: ");
			scanf("%d", &base);
			printf("Enter number: ");
			scanf("%d", &x);
			result = my_log(base, x);
			if (result == -1)
			{
				printf("Logarithm is not defined for base <= 1 or x <= 0.\n");
			}
			else
			{
				printf("Result: log_%d(%d) = %.2f\n", base, x, result);
			}
			break;
		}
		case 8:
		{
			int a, b, c;
			double root1, root2;

			printf("For the quadratic equation ax^2 + bx + c = 0,\n");
			a = readInt("Enter a (non-zero): ");
			if (a == 0)
			{



printf("Coefficient a cannot be zero for a quadratic equation.\n");
				break;
			}
			b = readInt("Enter b: ");
			c = readInt("Enter c: ");

			my_quadratic_solver(a, b, c, &root1, &root2);

			if (root1 == -1 && root2 == -1)
			{
				printf("The equation has no real roots.\n");
			}
			else
			{
				printf("The roots of the equation are: %.2f and %.2f\n", root1, root2);
			}
			break;
		}
		default:
			printf("Please select a valid option from 1 to 8.\n");
			break;
		}

		printResultLine();
		printf("Returning to menu...\n");
	}

	return 0;
}
