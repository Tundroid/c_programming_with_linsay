#include <stdio.h>

struct country
{
    int surface_area;
    int population;
    float birth_rate;
    float death_rate;
    char capital[20];
    char currency[4];
    char president[20];
};
int main()
{
    struct country c1[4];

    int i;

     
    
    for (i = 0; i < 4; i++)
    {
        printf("Enter name of country %d: ", i + 1);
        scanf("%s", c1[i].capital);
        printf("Enter surface area of country %d: ", i + 1);
        scanf("%d", &c1[i].surface_area);
        printf("Enter population of country %d: ", i + 1);
        scanf("%d", &c1[i].population);
        printf("Enter birth rate of country %d: ", i + 1);
        scanf("%f", &c1[i].birth_rate);
        printf("Enter death rate of country %d: ", i + 1);
        scanf("%f", &c1[i].death_rate);
        printf("Enter currency of country %d: ", i + 1);
        scanf("%s", c1[i].currency);
        printf("Enter president of country %d: ", i + 1);
        scanf("%s", c1[i].president);
    }
    printf("\n__ Country Information __\n");
    for (i = 0; i < 4; i++)
    {
        printf("\n name: %10s | Surface Area: %10d | Population: %10d | Birth Rate: %5.2f | Death Rate: %5.2f | Currency: %4s | President: %20s\n",
               c1[i].capital, c1[i].surface_area, c1[i].population, c1[i].birth_rate, c1[i].death_rate, c1[i].currency, c1[i].president);
    }

    return 0;
}