/**
 * @file euclid.c
 * @author 0x5a (felix@moleculesoft.net)
 * @brief Implementation of the Euclidean algorithm for computing the greatest common divisor (GCD) of two integers.
 * @version 1.0
 * @date 2024-06-01
 */

#include <stdio.h>

/**
 * @brief Computes the greatest common divisor (GCD) of two integers using the Euclidean algorithm.
 *
 * @param a First integer
 * @param b Second integer
 * @return The greatest common divisor of a and b
 */
int gcd(int a, int b) {
    int count = 0; // Counter to track the number of iterations
    while (b != 0) {
        printf("Current values: a = %d, b = %d\n", a, b); // Debug statement to trace the values of a and b
        int temp = b;
        b = a % b;
        a = temp;
        count++; // Increment the iteration counter
    }
    printf("Number of iterations: %d\n", count); // Print the number of iterations
    return a;
}
int main() {
    int num1, num2;
    printf("Enter two integers: ");
    scanf("%d %d", &num1, &num2);
    int result = gcd(num1, num2);
    printf("The GCD of %d and %d is %d\n", num1, num2, result);
    return 0;
}