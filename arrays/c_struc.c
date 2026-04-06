#include <stdio.h>
struct student
{
   int age;
   float grade;
};

int main(){
    struct student s1;
    printf("enter the age");
    scanf("%d",& s1.age);
    printf("enter the grade");
    scanf("%f",&s1.grade);
printf("\n __ student information __");
printf("\n age : %d",s1.age);
printf("\n grade : %f",s1.grade);

    return 0;
}