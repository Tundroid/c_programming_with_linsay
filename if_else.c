 #include <stdio.h>
int main(){

    int num;
    printf("enter number:");
    scanf("%d",&num);
 if (num>0)
    {
        printf("is a positive number");
    }
        else if (num==0)
        {
            printf("is equals to 0");
        }
        
    else if (num<0)
    {
        printf("is a negative number");
    }
    return 0;
}