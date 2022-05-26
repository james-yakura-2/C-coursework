#include <stdio.h>
#include "bit_flags.h"

void bit_flags_display(BIT_FLAGS);

int main(int argl, char* args)
{
	BIT_FLAGS flags = bit_flags_init_number_of_bits(32);
	if (flags != NULL)
	{
		printf("Flags created.\n");
	}
	bit_flags_display(flags);
	
	bit_flags_set_flag(flags, 3);
	bit_flags_set_flag(flags, 21);
	bit_flags_display(flags);
	bit_flags_set_flag(flags, 45);
	bit_flags_display(flags);
	bit_flags_unset_flag(flags, 3);
	bit_flags_display(flags);
	bit_flags_unset_flag(flags, 63);
	bit_flags_display(flags);

	bit_flags_destroy(&flags);
	if (flags == NULL)
	{
		printf("Flags destroyed.\n");
	}

}

void bit_flags_display(BIT_FLAGS input)
{
	int size = bit_flags_get_size(input);
	for (int i = 0; i < size; i++)
	{
		printf("%d", bit_flags_check_flag(input, i));
	}
	printf(" Size: %d. Capacity: %d.\n", bit_flags_get_size(input), bit_flags_get_capacity(input));
}