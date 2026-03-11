#include <stdio.h>

int main(){
	int yob, cur_year;
	
	printf("Welcome User!\n");
	printf("Enter your year of birth: ");
	scanf("%d", &yob);
	printf("Enter current year: ");
	scanf("%d", &cur_year);

	printf("You are %d years old!", (cur_year - yob));
	return 0;
}
