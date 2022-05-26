#pragma once

#include <stdio.h>

/***********************************************************
Author: James
Date: 9/9/19
Effort: 0:20
Purpose: To practice use of the left-shift operator.
***********************************************************/

int main2(char args[], int arg_length)
{
	unsigned int num = 1;
	for (int index = 0; num > 0; index++)
	{
		printf("%i: %u\n", index, num);
		num = num << 1;
	}

	return 0;
}