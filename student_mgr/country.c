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

    return 0;
}