#include <stdio.h>
int main()
{
    float marks[3][3];
    float sum, average;

    for (int i = 0; i < 3; i++)
    {
        printf("enter marks for student %d:\n", i + 1);
        for (int j = 0; j < 3; j++)
        {
            scanf("%f", &marks[i][j]);
        }
    }
    for (int i = 0; i < 3; i++)

    {
        sum = 0;

        for (int j = 0; j < 3; j++)
        {
            sum += marks[i][j];
        }
        average = sum / 3;
        printf("student %d average=|%.2f\n", i + 1, average);
    }
    return 0;
}