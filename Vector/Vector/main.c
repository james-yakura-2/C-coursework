#include <stdio.h>
#include "../vector.h"

int main(int argl, int* argv)
{
	VECTOR vect = NULL;
	vect=vector_init_default();
	printf("Vector created.\n");

	vector_destroy(&vect);
}