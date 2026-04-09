#include <stdio.h>

/**
 * Function to determine the grade based on the average marks
 * @param average The average marks of the student
 * @return The grade corresponding to the average marks
 */
char get_grade(float average)
{
    if (average >= 90)
        return 'A';
    else if (average >= 80)
        return 'B';
    else if (average >= 70)
        return 'C';
    else if (average >= 60)
        return 'D';
    else
        return 'F';
}

struct student
{
    char name[20];
    float marks[3];
    float average;
    char grade;
};

// or SUBJECTS[3] = {"Math", "Physics", "Chemistry"};
const char *SUBJECTS[] = {"Math", "Physics", "Chemistry"};

int main()
{
    struct student s1[3];

    int i, j;

    for (i = 0; i < 3; i++)
    {
        printf("Enter name of student %d: ", i + 1);
        scanf("%s", s1[i].name);

        int sum = 0;
        for (j = 0; j < 3; j++)
        {
            printf("Enter mark for %s: ", SUBJECTS[j]);
            scanf("%f", &s1[i].marks[j]);
            sum += s1[i].marks[j];
        }
        s1[i].average = sum / 3.0;
        s1[i].grade = get_grade(s1[i].average);
    }

    printf("\n_____Report Card_____\n");

    for (i = 0; i < 3; i++)
    {
        printf("\nName: %20s | Average: %5.2f | Grade: %c\n", s1[i].name, s1[i].average, s1[i].grade);
    }
    return 0;
}