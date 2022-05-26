#pragma once
#include <stdio.h>

int main1(int argc, char* argv[])
{
	char word[] = "Happy birthday";
	printf("%s\n", word);
	reverse2(word, sizeof(word)/sizeof(word[0])-1);
	printf("%s\n", word);
	printf("%s\n", reverse2(word,sizeof(word)/sizeof(word[0])-1));
	printf("%s\n", word);

	printf("%s\n", word);
	reverse(word);
	printf("%s\n", word);
	printf("%s\n", reverse(word));
	printf("%s\n", word);

	return 0;
}

