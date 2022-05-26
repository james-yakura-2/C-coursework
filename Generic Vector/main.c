#include <stdio.h>
#include <stdlib.h>
#include "gen_vector.h"

void a(void) {
	printf("Func a\n");
}

void b(void) {
	printf("Func b\n");
}

int main(int argc, char* argv[]) {
	//example of pointer to func
	a();
	b();
	void (*p)(void);
	p = a;
	void (*pp[2])(void);
	pp[0] = a;
	pp[1] = b;

	pp[1]();
	//-----
	G_VECTOR hG_Vector = NULL;
	hG_Vector = g_vector_init_default(int_assign, int_destroy);

	if (hG_Vector == NULL) {
		printf("Did not creat generic vector\n");
		exit(1);
	}
	int x = 1;
	int i;
	printf("Before push_back\n");
	i = 10;
	g_vector_push_back(hG_Vector, &i);
	for (i = 0; i < 6; ++i)
		g_vector_push_back(hG_Vector, &i);
	printf("After push_back\n");

	printf("size=%d\tcapacity=%d\n", g_vector_get_size(hG_Vector),
		g_vector_get_capacity(hG_Vector));
	printf("After get_size and capacity\n");
	for (i = 0; i < g_vector_get_size(hG_Vector); ++i) {
		//printf("i= %d size= %d\n", i, g_vector_get_size(hG_Vector));
		printf("%d\n", *(int*)g_vector_at(hG_Vector, i));
	}
	printf("After print before destroy\n");
	g_vector_destroy(&hG_Vector);
	
	return 0;
}