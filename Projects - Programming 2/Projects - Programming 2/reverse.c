int reverse(char word[])
{
	//Find length of character array, so that reversal is possible. 
	int length = find_length(word);
	//printf("Length: %d\n", length); //Debug message.
	//Iterating halfway through the length, swap the character at position x with the character at position len-x.
	for(int index=0;index<length/2;index++)
	{
		int other_index = length - index - 1;
		//printf("Swapping %c with %c\n",word[index],word[other_index]); //Debug message.
		char swap = word[index];
		word[index] = word[other_index];
		word[other_index] = swap;
	}

	return word;
}

int reverse2(char word[], int length)
{
	//Iterating halfway through the length, swap the character at position x with the character at position len-x.
	for (int index = 0; index < length / 2; index++)
	{
		int other_index = length - index - 1;
		//printf("Swapping %c with %c\n", word[index], word[other_index]); //Debug message.
		char swap = word[index];
		word[index] = word[other_index];
		word[other_index] = swap;
	}
	return word;
}

int find_length(char word[])
{
	int value = 0;
	int index = 0;
	while (1==1)
	{
		if (word[index] == '\0')
		{
			value = index;
			break;
		}
		else
		{
			index++;
		}
	}
	return value;
}