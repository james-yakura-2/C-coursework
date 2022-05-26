#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
struct node;
typedef struct node Node;
struct node {
	int data;
	Node* next;
};

struct stack {
	Node* head;
};

typedef struct stack Stack;

STACK stack_init_default() {
	Stack* pStack = NULL;
	pStack = (Stack*)malloc(sizeof(Stack));
	if (pStack != NULL) {
		pStack->head = NULL;
	}
	return pStack;
}

Status stack_push(STACK hStack, int item) {
	Stack* pStack = (Stack*)hStack;
	Node* tmp = (Node*)malloc(sizeof(Node));
	if (tmp == NULL)
		return FAILURE;
	tmp->data = item;
	tmp->next = pStack->head;
	pStack->head = tmp;
	return SUCCESS;
}
Status stack_pop(STACK hStack) {
	Stack* pStack = (Stack*)hStack;
	Node* tmp;
	if(pStack->head==NULL)			
		return FAILURE;
	tmp = pStack->head;
	pStack->head = pStack->head->next;
	free(tmp);
	return SUCCESS;
}
int stack_top(STACK hStack, Status* pStatus) {
	Stack* pStack = (Stack*)hStack;
	if (stack_empty(hStack))
	{
		if (pStatus != NULL)
		{
			*pStatus = FAILURE;
		}
		return INT_MIN;
	}
	if (pStatus != NULL)
	{
		*pStatus = SUCCESS;
	}
	return pStack->head->data;
}

//is empty?
Boolean stack_empty(STACK hStack) {
	Stack* pStack = (Stack*)hStack;
	return (Boolean)(pStack->head==NULL);
}

//destroy object
void stack_destroy(STACK* phStack) {
	Stack* pStack = (Stack*)*phStack;
	Node* tmp;
	while (pStack->head != NULL) {
		tmp = pStack->head;
		pStack->head = pStack->head->next;
		free(tmp);
	}
	free(pStack);
	*phStack = NULL;
}

