#pragma once

/***********************************************************
Author: James
Date: 9/12/19
Effort: 0:45
Purpose: To practice use of bitwise operators such as &, |, <<, and >>.
***********************************************************/

#include <stdio.h>
void set_flag2(int* flag_holder, int flag_position)
{
	int flag = 1 << flag_position;
	//printf("%d, ", flag); //Debug code.
	//printf("%d, ", (flag | *flag_holder)); //Debug code.
	//printf("%d, ", flag + *flag_holder); //Debug code.
	*flag_holder = flag | *flag_holder;

	//printf("%d\n", *flag_holder); //debug code
}
int check_flag2(int flag_holder, int flag_position)
{
		return 1 & (flag_holder >> flag_position);
}
int main3(int argc, char* argv[])
{
	int flag_holder = 0;
	int i;
	set_flag(&flag_holder, 3);
	set_flag(&flag_holder, 16);
	set_flag(&flag_holder, 31);
	for (i = 31; i >= 0; i--)
	{
		printf("%d", check_flag(flag_holder, i));
		if (i % 4 == 0)
		{
			printf(" ");
		}
	}
	printf("\n");
	//printf("%d", flag_holder);//Debug code.
	return 0;
}