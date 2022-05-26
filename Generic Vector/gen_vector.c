#include "gen_vector.h"
struct g_vector {
	int size;
	int capacity;
	Item_ptr data;
	Status (*item_assign)(Item_ptr, Item );
	void (*item_destroy)(Item_ptr);
};
typedef struct g_vector G_Vector;

Status int_assign(Item_ptr phLeft, Item hRight) {
	int* pLeft = (int*)*phLeft;
	int* pRight = (int*)hRight;
	if (pLeft == NULL) {
		pLeft = (int*)malloc(sizeof(int));
		if (pLeft == NULL) {
			printf("Failed to assign\n");
			return FAILURE;
		}
		*phLeft = pLeft;
	}
	*pLeft = *pRight;
	return SUCCESS;
}

void int_destroy(Item_ptr phLeft) {
	int* pLeft = (int*)*phLeft;
	free(pLeft);
	*phLeft = NULL;
}
 
G_VECTOR g_vector_init_default(Status(*item_assign)(Item_ptr, Item),
	void (*item_destroy)(Item_ptr)) {
	G_Vector* pVector = NULL;
	int i;
	pVector = (G_Vector*)malloc(sizeof(G_Vector));
	if (pVector != NULL) {
		pVector->size = 0;
		pVector->capacity = 1;
		pVector->item_assign = item_assign;
		pVector->item_destroy = item_destroy;
		pVector->data = (Item_ptr)malloc(sizeof(void*)* pVector->capacity);
		if (pVector->data == NULL) {
			free(pVector);
			pVector = NULL;
		}
		else {
			for (i = 0; i < pVector->capacity; ++i)
				pVector->data[i] = NULL;
		}
	}
	return pVector;
}
//use vector
int g_vector_get_capacity(G_VECTOR hG_Vector) {
	G_Vector* pVector = (G_Vector*)hG_Vector;
	return pVector->capacity;
}
int g_vector_get_size(G_VECTOR hG_Vector) {
	G_Vector* pVector = (G_Vector*)hG_Vector;
	return pVector->size;
}
Status g_vector_push_back(G_VECTOR hG_Vector, Item item) {
	G_Vector* pG_Vector = (G_Vector*)hG_Vector;
	Item_ptr temp;
	int i;
	if (pG_Vector->size >= pG_Vector->capacity) {
		temp = (Item_ptr)malloc(sizeof(Item) * 2* pG_Vector->capacity );
		if (temp == NULL) {
			return FAILURE;
		}

		for (i = 0; i < pG_Vector->capacity; ++i) {
			temp[i] = pG_Vector->data[i];
		}
		pG_Vector->capacity *= 2;
		for (i = pG_Vector->size; i < pG_Vector->capacity; ++i)
			temp[i] = NULL;

		free(pG_Vector->data);
		pG_Vector->data = temp;
	}
	pG_Vector->item_assign(&pG_Vector->data[pG_Vector->size],item);
	pG_Vector->size++;
	return SUCCESS;
}
Status g_vector_pop_back(G_VECTOR hG_Vector) {
	G_Vector* pVector = (G_Vector*)hG_Vector;
	if (pVector->size <= 0)
		return FAILURE;
	pVector->size--;
	return SUCCESS;
}
Item g_vector_at(G_VECTOR hG_Vector, int index) {
	G_Vector* pVector = (G_Vector*)hG_Vector;
	if (index < 0 || index >= pVector->size)
		return NULL;

	return pVector->data[index];
}
//destroy
void g_vector_destroy(G_VECTOR* phG_Vector) {
	G_Vector* pVector = (G_Vector*)* phG_Vector;
	int i;

	for (i = 0; i < pVector->capacity; ++i) {
		if (pVector->data[i] != NULL)
			pVector->item_destroy(&pVector->data[i]);
	}
	free(pVector->data);
	free(pVector);
	*phG_Vector = NULL;
}