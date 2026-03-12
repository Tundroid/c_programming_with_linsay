#include <stdio.h>

int main(){
    int Num1,Num2;

    printf("welcome user!\n");
    printf("Enter Num1: ");
    scanf("%d",&Num1);
    printf("Enter Num2: ");
    scanf("%d",&Num2);  

    if (Num2 == 0) {
        printf("Division by 0 not allowed!");
        return 1;
    }

    printf("%d / %d = %.2f", Num1, Num2, ((float) Num1/Num2));
    
    return 0;
}