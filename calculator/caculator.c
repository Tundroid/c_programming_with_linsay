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
	printf("|         LINDSAY'S FANCY CALCULATOR       |\n");
	printf("+------------------------------------------+\n");
	printf("| 1. Power (base^exp)                      |\n");
	printf("| 2. Square                                |\n");
	printf("| 3. Cube                                  |\n");
	printf("| 4. Integer square root                   |\n");
	printf("| 5. Factorial                             |\n");
	printf("| 6. Absolute value                        |\n");
	printf("| 7. Exit                                  |\n");
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
		option = readInt("Select an option (1-7): ");

		if (option == 7)
		{
			printf("\nThanks for using Lindsay's Fancy Calculator. Bye!\n");
			break;
		}

		printResultLine();

		switch (option)
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
				n = readInt("Enter number: ");
				answer = square(n);
				printf("Result: square(%d) = %d\n", n, answer);
				break;

			case 3:
				n = readInt("Enter number: ");
				answer = cube(n);
				printf("Result: cube(%d) = %d\n", n, answer);
				break;

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

			case 6:
				n = readInt("Enter number: ");
				answer = my_abs(n);
				printf("Result: abs(%d) = %d\n", n, answer);
				break;

			default:
				printf("Please select a valid option from 1 to 7.\n");
				break;
		}

		printResultLine();
		printf("Returning to menu...\n");
	}

	return 0;
}
