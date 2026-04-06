#include <stdio.h>
struct rectangle
{
    float length;
    float width;
};
int main()
{
    struct rectangle r1;
    printf("enter the length");
    scanf("%f", &r1.length);
    printf("enter the width");
    scanf("%f", &r1.width);
    float area = r1.length * r1.width;
    printf("\n __ rectangle information __");
    printf("\n length : %.2f", r1.length);
    printf("\n width : %.2f", r1.width);
    printf("\n area : %.2f", area);
    return 0;
}