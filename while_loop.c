#include <stdio.h>
int main(){
    int num;

    printf("enter a num");
    scanf("%d ",&num);
    int count =10;

    while (count >=1)
    {
        int product=num*count;
    
    printf("%d*%d=%d\n",num,count,product);
    count=count-1;
    }
    return 0;
}