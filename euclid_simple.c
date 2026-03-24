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
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
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