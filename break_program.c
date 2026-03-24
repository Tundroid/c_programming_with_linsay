#include <stdio.h>
int main(){
    int num;
    while (1)
    {
    printf("Enter number");
    scanf("%d ",&num);
    if (num==0)
    {
        break; //stops the loop
    
    }
    if (num<0)
    {    
    printf("negative numbers: %d\n",num);
    }
    }
    return 0;
    }
    
