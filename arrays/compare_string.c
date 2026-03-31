#include <stdio.h>
#include <string.h>
int main()
{
    char str1[20], str2[20];
    printf("enter first string:");
    gets(str1);
    printf("enter second string:");
    gets(str2);
    if (strcmp(str1, str2) == 0)
    {
        printf("both strings are same");
    }
    else
    {
        printf("both strings are different");
    }
    return 0;
}