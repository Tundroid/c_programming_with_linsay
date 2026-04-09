#include <stdio.h>
struct student
{
    char name[20];
    float marks[3];
    float average[3];
    char grade[3];
};
int main()
{
    struct student s1[3];
    int i,j;
    for (i = 0; i < 3; i++)
    {
        printf(" enter name of student %d:", i + 1);
        scanf("%s", s1[i].name);
    }
    for (j = 0; j < 3; j++)
    {
        s1[i].average = 0;
        printf("enter mark for subject %d:", j + 1);
        scanf("%f", &s1[i].marks[j]);
        s1[i].average=(s1[i].average + s1[i].marks[j]) / 3;
        scanf("%f", &s1[i].average);
    }

    if (s1[i].average >= 90)
    {
        s1[i].grade = 'A';
    }
    else if (s1[i].average >= 80)
    {
        s1[i].grade = 'B';
    }
    else if (s1[i].average >= 70)
    {
        s1[i].grade = 'C';
    }
    else if (s1[i].average >= 60)
    {
        s1[1].grade[i] = 'D';
    }
    else
    {
        s1[i].grade = 'F';
    }
    printf("\n_____report card_____");

    printf("name\t\tbiology\t\tchemistry\t\tphysics\t\taverage\t\tgrade\n");

    for (i = 0; i < 3; i++)
    {
        printf("%-10\t", s1[i].name);
        for (int j = 0; j < 3; j++)
            printf("%.2f\t", s1[i].marks[j]);
        printf("%.2f\t", s1[i].average);
        printf("%c\t", s1[i].grade);
    }
    return 0;
}