#include <stdio.h>
int main()
{
    float M1, M2, M3, M4, M5;
    float sum, average;

    printf("Enter marks for 5 subjects:\n");
    scanf("%f %f %f %f %f", &M1, &M2, &M3, &M4, &M5);

    sum = M1 + M2 + M3 + M4 + M5;
    average = sum / 5;

    printf("average mark=%.2f\n", average);

    return 0;
}