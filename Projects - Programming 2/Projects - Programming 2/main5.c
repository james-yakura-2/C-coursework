#pragma once
#include <stdio.h>


/***********************************************************
Author: James
Date: 9/17/19
Effort: 0:50
Purpose: To practice use of bitwise operations and arrays.
***********************************************************/

const int bits_per_int5 = 32;

void set_flag5(unsigned int flag_holder[], int flag_position)
{
	int index = flag_position / bits_per_int5;
	int shift = flag_position % bits_per_int5;
	unsigned int flag = 1 << shift;
	flag_holder[index] = flag_holder[index] | flag;
}
void unset_flag5(unsigned int flag_holder[], int flag_position)
{
	int index = flag_position / bits_per_int5;
	int shift = flag_position % bits_per_int5;
	unsigned int flag = 1 << shift;
	flag_holder[index] = flag_holder[index] & ~flag;
}
int check_flag5(unsigned int flag_holder[], int flag_position)
{
	int index = flag_position / bits_per_int5;
	int shift = flag_position % bits_per_int5;
	return (flag_holder[index] >> shift) & 1;
}
void display_32_flags_as_array5(unsigned int flag_holder)
{
	int flag_pass[] = { flag_holder };
	for (int index = 0; index < bits_per_int5; index++)
	{
		printf("%d", check_flag5(flag_pass, index));
		if (index % 4 == 3)
		{
			printf(" ");
		}
	}
	printf("\n");
}
void display_flags5(unsigned int flag_holder[], int size)
{
	for (int index = 0; index < size; index++)
	{
		display_32_flags_as_array5(flag_holder[index]);
	}
}
int main5(int argc, char* argv[])
{
	unsigned int flag_holder[5] = { 0 };//Set the first integer to zero and all others to zero by default.
	set_flag5(flag_holder, 3);
	set_flag5(flag_holder, 16);
	set_flag5(flag_holder, 31);
	set_flag5(flag_holder, 87);
	display_flags5(flag_holder, 5);
	printf("\n\n");
	unset_flag5(flag_holder, 31);
	unset_flag5(flag_holder, 3);
	set_flag5(flag_holder, 99);
	set_flag5(flag_holder, 100);
	display_flags5(flag_holder, 5);
	return 0;
}