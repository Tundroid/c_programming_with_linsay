#include <stdio.h>

int main(){
    int  num; 
    printf(" enter num ");
    scanf("%d",&num );

    if(num %2==0 && num % 5!=0){
        printf("%d is an even number\n",num);
        printf("%d list all even num ofthat num\n",num);
     } else{
        printf("%d is not an even number\n ",num);
     }
    return 0;
     }


