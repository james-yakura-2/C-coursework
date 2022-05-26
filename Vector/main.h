#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "status.h"
typedef void* VECTOR;

//init
VECTOR vector_init_default(void);
//use vector
int vector_get_capacity(VECTOR hVector);
int vector_get_size(VECTOR hVector);
Status vector_push_back(VECTOR hVector, int item);  //insert new item
Status vector_pop_back(VECTOR hVector);
int* vector_at(VECTOR hVector, int index);
//destroy
void vector_destroy(VECTOR* phVector);