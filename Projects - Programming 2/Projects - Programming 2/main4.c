/***********************************************************
Author: James Yakura
Date: 9/15/19
Effort: 0:10
Purpose: To practice use of bitwise operators and shift operators.
***********************************************************/

#include <stdio.h>
void set_flag4(unsigned int* flag_holder, int flag_position) //Copied from Daily 3
{
	int flag = 1 << flag_position;
	*flag_holder = flag | *flag_holder;

}
void unset_flag4(unsigned int* flag_holder, int flag_position)
{
	int flag = 1 << flag_position;
	flag = ~flag;
	*flag_holder = flag & *flag_holder;
}
int check_flag4(unsigned int flag_holder, int flag_position) //Copied from Daily 3
{
	return 1 & (flag_holder >> flag_position);
}
void display_32_flags4(unsigned int flag_holder) //Copied from given code in Daily 3
{
	for (int i = 31; i >= 0; i--)
	{
		printf("%d", check_flag4(flag_holder, i));
		if (i % 4 == 0)
		{
			printf(" ");
		}
	}
	printf("\n");
}
int main4(int argc, char* argv[])
{
	unsigned int flag_holder = 0;
	set_flag4(&flag_holder, 3);
	set_flag4(&flag_holder, 16);
	set_flag4(&flag_holder, 31);
	display_32_flags4(flag_holder);
	unset_flag4(&flag_holder, 31);
	unset_flag4(&flag_holder, 3);
	set_flag4(&flag_holder, 9);
	display_32_flags4(flag_holder);
	return 0;
}