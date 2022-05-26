#include <stdio.h>

int main(int argc, char* argv[])
{
	int* p; //Declaration of a pointer variable.
	p = (int*)malloc(sizeof(int) * 100); //First "bookend" allocates space
	printf("Hello world! I have created a dynamic array of 100 integers!\n");
	free(p); //Second "bookend" cleans up the space
	return 0;
}