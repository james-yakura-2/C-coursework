#include "stdlib.h"
#include "stdio.h"
#include "stack.h"

struct stack{
	int size;
	int capacity;
	int* data;
};
typedef struct stack Stack;

STACK stack_init_default() {
	Stack* pStack = NULL;
	pStack = (Stack*)malloc(sizeof(Stack));
	if (pStack != NULL) {
		pStack->size = 0;
		pStack->capacity = 10;
		pStack->data = (int*)malloc(sizeof(int)*pStack->capacity);
		if (pStack->data == NULL) {
			free(pStack);
			pStack = NULL;
		}
	}
	return pStack;
}

//push
//Precondition: hStack is handle to a valid object
//Postconditions: return SUCCESS if item was added

Status stack_push(STACK hStack, int item) {
	Stack* pStack = (Stack*)hStack;
	int* tmp;
	int i;
	if (pStack->size >= pStack->capacity) {
		tmp = (int*)malloc(sizeof(int)*pStack->capacity * 2);
		if (tmp == NULL) {
			return FAILURE;
		}
		for (i = 0; i < pStack->size; i++) {
			tmp[i] = pStack->data[i];
		}
		free(pStack->data);
		pStack->data = tmp;
		pStack->capacity *= 2;
	}
	pStack->data[pStack->size] = item;
	pStack->size++;
	return SUCCESS;
}

//pop
//Precondition: hStack is handle to a valid object
//Postconditions: return SUCCESS if item was removed
Status stack_pop(STACK hStack) {
	Stack* pStack = (Stack*)hStack;
	if (pStack->size <= 0)
		return FAILURE;
	pStack->size--;
	return SUCCESS;
}

//return top
int stack_top(STACK hStack, Status* pStatus) {
	Stack* pStack = (Stack*)hStack;
	if (stack_empty(hStack)) {
		if (pStatus != NULL)
			*pStatus = FAILURE;
		return INT_MIN;
}
	if (pStatus != NULL)
		*pStatus = SUCCESS;

	return pStack->data[pStack->size-1];
}

//is empty?
Boolean stack_empty(STACK hStack) {
	Stack* pStack = (Stack*)hStack;
	if (pStack->size == 0) {
		return TRUE;
	}
	return FALSE;
}
//destroy object
void stack_destroy(STACK* phStack) {
	Stack* pStack = (Stack*)*phStack;
	free(pStack->data);
	free(*phStack);
	*phStack = NULL;
}
