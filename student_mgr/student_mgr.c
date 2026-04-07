#include <stdio.h>

struct student
{
    char name[20];
    int age;
    float grade;
};

int main()
{
    struct student s1[3];

    for (int i = 0; i < 3; i++) {
        printf("Enter student name %d: ", i + 1);
        scanf("%s", s1[i].name);

        printf("Enter student age for %s: ", s1[i].name);
        scanf("%d", &s1[i].age);

        printf("Enter student grade for %s: ", s1[i].name);
        scanf("%f", &s1[i].grade);
    }

    printf("\n__ Student Information __\n");
    for (int i = 0; i < 3; i++) {
        printf("%d. Name: %20s | Age: %5d | Grade: %2.2f\n", i + 1, s1[i].name, s1[i].age, s1[i].grade);
    }   

    return 0;
}