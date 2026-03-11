#include <stdio.h>

int main() {
    int n, fac;

    printf("Enter n: ");
    scanf("%d", &n);

    fac = 1;

    for(int i = 1; i <= n; i++){
        fac = fac * i;
    }

    printf("%d! = %d", n, fac);

    return 0;
}