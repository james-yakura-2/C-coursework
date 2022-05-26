#include <stdio.h>
#include <stdlib.h>
#include "date.h"

int main(int argc, char* agrv[]) {
	DATE today; 
	today = date_init_default();
	if (today == NULL) {
		printf("not able to allocate memory\n");
		exit(1);
	}
	if (date_set_month(today, 9) == FAILURE)
		printf("incorect input\n");
	/*today.month = 9;
	today.day = 6;
	today.year = 2019;*/
	out_date(today);
	date_destroy(&today);
	if (today == NULL)
		printf("Destroyed!\n");
	return 0;
}