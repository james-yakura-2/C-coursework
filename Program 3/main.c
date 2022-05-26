/**********************************************************************
Program: Program 3
Author: James Yakura
Date: 11/25
Time spent: 3:00
Purpose: The purpose of this program is to take in a list of numbers, remove duplicates, and return a sorted list.
***********************************************************************/
#include <stdio.h>
#include <stdlib.h>


struct vector
{
	int size;
	int* data;
};
typedef struct vector Vector;

int main()
{
	Vector* numbers = NULL;
	numbers=(Vector*)malloc(sizeof(Vector));
	if (numbers == NULL)
	{
		printf("Error: Could not allocate numbers vector.\n");
		return 0;
	}
	numbers->size = 0;
	numbers->data = NULL;
	numbers->data = (int*)malloc(sizeof(int) * 1);
	if (numbers->data == NULL)
	{
		printf("Error: Could not initialize numbers vector.\n");
		free(numbers);
		return 0;
	}

	int running = 1;
	while (running)
	{
		int input=-1;
		scanf_s("%d", &input);
		//printf("Processing: %d\n", input);//Debug code.
		if (input < 0)
		{
			running = 0;
		}
		else
		{
			//Take in numbers, terminating with -1.
			//Perform insertion sort on each new number:
			//Iterate over vector of numbers.
			int* new_data = NULL;
			new_data = (int*)malloc(sizeof(int) * (numbers->size+1));
			if (new_data == NULL)
			{
				printf("Resize failed.\n");
				free(numbers->data);
				free(numbers);
				return 0;
			}
			int added = 0;
			if (numbers->size < 1)
			{
				new_data[0] = input;
				added = 1;
			}
			else
			{
				for (int i = 0; i <= numbers->size; i++)
				{
					if (input == numbers->data[i])
					{
						break;
					}
					else if (i >= numbers->size && !added)
					{
						//printf("Adding %d to end\n", input);//Debug code.
						new_data[i] = input;
						added = 1;
					}
					else if (input < numbers->data[i] && !added)
					{
						//printf("Inserting %d at postion %d\n", input, i);//Debug code.
						new_data[i] = input;
						added = 1;
					}
					if (added)
					{
						new_data[i + 1] = numbers->data[i];
					}
					else
					{
						new_data[i] = numbers->data[i];
					}
				}
			}
			if (added)
			{
				//printf("Adding input: %d\n", input);//Debug code.
				free(numbers->data);
				numbers->data = new_data;
				numbers->size++;
			}
			else
			{
				free(new_data);
			}
			//If match found, throw out number.
			//Otherwise, insert in order.
		}
	}

	//Output vector in order.

	//printf("Length: %d\n", numbers->size);//Debug code.
	for (int i = 0; i < numbers->size; i++)
	{
		printf("%d\n", numbers->data[i]);
	}
	free(numbers->data);
	free(numbers);

	return 1;
}