#include "status.h"

typedef void* VECTOR;
//init
VECTOR vector_init_default(void);
//add item
Status vector_push_back(VECTOR, int);
//remove item
Status vector_pop_back(VECTOR);
//check size and capacity
int vector_get_size(VECTOR);
int vector_get_capacity(VECTOR);
// see the particular item
int* vector_at(VECTOR, int);
//print the data



//destroy
void vector_destroy(VECTOR*);