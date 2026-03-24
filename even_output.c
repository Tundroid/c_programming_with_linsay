#include <stdio.h>
int main(){
    int num;
    printf("enter a number");

scanf("%d",&num);

    for(int i=0;i<num;++i)
    {
        if(num %2==0 )
        {                                      
            printf("%d, ",i++);
        }

    }
    
    return 0;
}
