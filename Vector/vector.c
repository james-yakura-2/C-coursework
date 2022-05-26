#include <stdio.h>
#include "vector.h"

struct vector {
	int size;
	int capacity;
	int* data;
};
typedef struct vector Vector;

VECTOR vector_init_default(void) {
	Vector* pVector = NULL;
	pVector = (Vector*)malloc(sizeof(Vector));
	if (pVector != NULL) {
		pVector->size = 0;
		pVector->capacity = 1;
		pVector->data = (int*)malloc(sizeof(int)*pVector->capacity);
		if (pVector->data == NULL) {
			free(pVector);
			pVector = NULL;
		}
	}
	return pVector;
}

Status vector_push_back(VECTOR hVector, int item) {
	Vector* pVector = (Vector*)hVector;
	int* tmp;
	int i;
	if (pVector->size >= pVector->capacity) {
		tmp = (int*)malloc(sizeof(int)*pVector->capacity * 2);
		if (tmp == NULL) {
			return FAILURE;
		}
		for (i = 0; i < pVector->capacity; i++) {
			tmp[i] = pVector->data[i];
		}
		free(pVector->data); pVector->data = tmp;
		pVector->capacity *= 2;
	}
	pVector->data[pVector->size] = item;
	pVector->size++;
	return SUCCESS;
}

Status vector_pop_back(VECTOR hVector) {
	Vector* pVector = (Vector*)hVector;
	if (pVector->size <= 0) {
		return FAILURE;
	}
	pVector->size--;
	return SUCCESS;
}
int vector_get_size(VECTOR hVector) {
	Vector* pVector = (Vector*)hVector;
	return pVector->size;
}
int vector_get_capacity(VECTOR hVector) {
	Vector* pVector = (Vector*)hVector;
	return pVector->capacity;
}

int* vector_at(VECTOR hVector, int index) {
	Vector* pVector = (Vector*)hVector;
	if (index < 0 || index >= pVector->capacity) {
		return NULL;
	}
	return &pVector->data[index];
}


void vector_destroy(VECTOR* phVector) {
	Vector* pVector = (Vector*)*phVector;
	free(pVector->data);
	free(pVector);
	*phVector = NULL;
}