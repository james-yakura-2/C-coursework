/***********************************************************
Author: James Yakura
Date: 9/19/19
Effort: 1:40
Purpose: To create a variable-length bit array.
 Interface proposal: Status bit_flags_truncate(BIT_FLAGS flags, int length). Reduces the length of the array, freeing memory and deleting flags that are no longer necessary.
***********************************************************/
#include <stdio.h>
#include "bit_flags.h"



struct bit_flags
{
	int num_ints;
	int* data;
	int bits_in_use;
};

typedef struct bit_flags Bit_Flags;

//Intentionally leaving out a default init function to force user to at least guess at the size needed.
//If one WERE to be used it would have the following prototype:
//BIT_FLAGS bit_flags_init_default(void);
//Precondition: number of bits is a positive integer.
//Postcondition: Returns the handle to a valid Bit_flags object that has the ability to store up to
// number_of_bits bits but currently all flags are set at zero. Returns NULL on failure. The container
// is assumed to hold size=number_of_bits after the init function runs.
BIT_FLAGS bit_flags_init_number_of_bits(int number_of_bits)
{
	Bit_Flags* pBit_Flags = NULL;
	pBit_Flags = malloc(sizeof(Bit_Flags));
	int number_of_ints = number_of_bits / 32;
	if (number_of_bits % 32 != 0)
	{
		number_of_ints++;
	}
	if (pBit_Flags != NULL)
	{
		pBit_Flags->num_ints = number_of_ints;
		pBit_Flags->bits_in_use = number_of_bits;
		pBit_Flags -> data = NULL;
		pBit_Flags->data = malloc(sizeof(int) * number_of_ints);
		if (pBit_Flags->data == NULL)
		{
			free(pBit_Flags);
			pBit_Flags = NULL;
		}
		else
		{
			for (int i = 0; i < pBit_Flags->num_ints; i++)
			{
				pBit_Flags->data[i] = 0;
			}
		}
	}

	return pBit_Flags;
}
//Precondition: flag_position is a non-negative integer and hBit_flags is a handle to a valid Bit_flags object.
//Postcondition: The flag at the flag_position index is set to 1. Function will attempt to resize the
// internal representation if the flag_position is too large instead of failing for out of bounds. Returns
// SUCCESS if the operation is successful and FAILURE if the operation fails a needed resize. This
// operation is considered to be expensive if flag_position is constantly going out of bounds by a small
// amount because the resize always attempts to minimize the amount of space required to store the bits.
// All new flags created in a resize operation (except the one being set) will be set as zero.
Status bit_flags_set_flag(BIT_FLAGS hBit_flags, int flag_position)
{
	Bit_Flags* pBit_flags = (Bit_Flags*)hBit_flags;
	int array_index = flag_position / 32;
	//Extend the array if necessary.
	if (pBit_flags->bits_in_use < flag_position + 1)
	{
		pBit_flags->bits_in_use = flag_position + 1;
	}
	if (array_index > pBit_flags->num_ints - 1)
	{
		int* new_data = NULL;
		new_data=malloc(sizeof(int) * (array_index + 1));
		if (new_data == NULL)
		{
			return FAILURE;
		}
		//Copy the old values into the new array.
		for (int i = 0; i <= array_index; i++)
		{
			if (i < pBit_flags->num_ints)
			{
				new_data[i] = pBit_flags->data[i];
			}
			else
			{
				new_data[i] = 0;
			}
		}
		//Update the array size and capacity values.
		pBit_flags->num_ints = array_index + 1;
		//Release the memory for the old array, and replace with the new array.
		free(pBit_flags->data);
		pBit_flags->data = new_data;
	}
	//Set the flag.
	int flag = 1 << flag_position % 32;
	pBit_flags->data[array_index] = pBit_flags->data[array_index] | flag;
	return SUCCESS;
}
//Precondition: flag_position is a non-negative integer and hBit_flags is a handle to a valid Bit_flags object.
//Postcondition: The flag at the flag_position index is set to 0. Function will attempt to resize the
// internal representation if the flag_position is too large instead of failing for out of bounds. Returns
// SUCCESS if the operation is successful and FAILURE if the operation fails a needed resize. This
// operation is considered to be expensive if flag_position is constantly going out of bounds by a small
// amount because the resize always attempts to minimize the amount of space required to store the bits.
// All new flags created in a resize operation will be set as zero.
Status bit_flags_unset_flag(BIT_FLAGS hBit_flags, int flag_position)
{
	Bit_Flags* pBit_flags = (Bit_Flags*)hBit_flags;
	int array_index = flag_position / 32;
	//Extend the array if necessary.
	if (pBit_flags->bits_in_use < flag_position + 1)
	{
		pBit_flags->bits_in_use = flag_position + 1;
	}
	if (array_index > pBit_flags->num_ints - 1)
	{
		int* new_data = NULL;
		new_data = malloc(sizeof(int) * (array_index + 1));
		if (new_data == NULL)
		{
			return FAILURE;
		}
		//Copy the old values into the new array.
		for (int i = 0; i <= array_index; i++)
		{
			if (i < pBit_flags->num_ints)
			{
				new_data[i] = pBit_flags->data[i];
			}
			else
			{
				new_data[i] = 0;
			}
		}
		//Update the array size and capacity values.
		pBit_flags->num_ints = array_index + 1;
		//Release the memory for the old array, and replace with the new array.
		free(pBit_flags->data);
		pBit_flags->data = new_data;
	}
	//Unset the flag.
	int flag = 1 << flag_position % 32;
	flag = ~flag;
	pBit_flags->data[array_index] = pBit_flags->data[array_index] & flag;
	return SUCCESS;
}
//Precondition: flag_position is a non-negative integer and hBit_flags is a handle to a valid Bit_flags object.
//Postcondition: returns the value of the flag at index flag_position if it is in bounds or -1 otherwise.
int bit_flags_check_flag(BIT_FLAGS hBit_flags, int flag_position)
{
	Bit_Flags* pBit_flags = (Bit_Flags*)hBit_flags;
	//Check for flag in bounds.
	if (flag_position < 0 || flag_position>=pBit_flags->bits_in_use)
	{
		return -1;
	}
	//Find correct int, and get the value.
	return (pBit_flags->data[flag_position / 32] >> flag_position % 32) & 1;

}
//Precondition: hBit_flags is a handle to a valid Bit_flags object.
//Postcondition: returns the number of bits currently held by the data structure.
int bit_flags_get_size(BIT_FLAGS hBit_flags)
{
	Bit_Flags* pBit_flags = (Bit_Flags*)hBit_flags;
	return pBit_flags->bits_in_use;
}
//Precondition: hBit_flags is a handle to a valid Bit_flags object.
//Postcondition: returns the number of bits the object CAN hold.
int bit_flags_get_capacity(BIT_FLAGS hBit_flags)
{
	Bit_Flags* pBit_flags = (Bit_Flags*)hBit_flags;
	return pBit_flags->num_ints * 32;
}
//Precondition: phBit_flags is the address of a handle to a valid Bit_flags object.
//Postcondition: The memory for the object referred to by the handle is free'd and the handle is set to NULL.
void bit_flags_destroy(BIT_FLAGS* phBit_flags)
{
	Bit_Flags* pBit_flags = (Bit_Flags*)*phBit_flags;
	free(pBit_flags->data);
	free(pBit_flags);
	*phBit_flags = NULL;
}