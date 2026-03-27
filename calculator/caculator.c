#include <stdio.h>
#include "library.c"
#include<math.h>
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
	printf("| 7. logarithm                            |\n");
	printf("| 8. Exit                                  |\n");
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
		option = readInt("Select an option (1-8): ");

		if (option == 8)
		{
			printf("\nThanks for using Linsay's Fancy Calculator. Bye!\n");
			break;
		}

		printResultLine();
		int choice;
double a, b,base,result;
printf("logarithm operations:\n");
printf("enter base:");
scanf("%lf",&base);
printf("\nchooseoperations:\n");
printf("1=log(a*b)\n");
printf("2=log(a/b)\n");
printf("3=log(a^b)\n");
printf("4=log(1)\n");
printf("5=log(base)\n");
printf("6=log(a)change of base\n");
printf("7=inverse(base^log_base(a))\n");
printf("enter your choice:");
scanf("%d",&choice);


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
if(choice==1){       //product rule
	printf("enter a and b:");
	scanf("%lf%lf",&a,&b);
	result=log(a*b)/log(base);
	printf("Result: %.4lf\n",result);
}
else if (choice == 2){      //quotient rule
	printf("enter a and b:");
	scanf("%lf%lf",&a,&b);
	result=log(a/b)/log(base);
	printf("Result: %.4lf\n", result);
}
else if (choice == 3){      //power rule
	printf("enter a and power b:");
	scanf("%lf%lf",&a,&b);			
result=log(pow(a,b))/log(base);
	printf("Result: %.4lf\n",result);
}
else if (choice == 4){      //LOG OF 1
	result=0;
	printf("Result: %.4lf\n", result);
}
else if (choice == 5){    //LOG OF BASE
	result=1;
	printf("result=%.4lf\n", result);	

}
else if (choice ==6 ){       //change of base
	printf("enter a,b :");
	scanf("%lf%lf",&a,&b);
result=log(a)/log(base);
	printf("Result: =%.4lf\n", result);
}

else if (choice == 7){       //inverse
	printf("enter a :");
	scanf("%lf",&a);
	result=pow(base,log(a)/log(base));
	printf("Result: =%lf\n", result);

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


