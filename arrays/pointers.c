#include <stdio.h>
int main()
{
    double salary;
    double *ptr;
    ptr = &salary;
    printf("enter salary:");
    scanf("%lf", &salary);
    *ptr = *ptr + 1000;
    printf("new salary=%.2lf\n", salary);

    return 0;
}    