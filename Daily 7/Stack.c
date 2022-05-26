#include "Stack.h"
typedef struct node Node;

struct node
{
	char data;
	Node* next;
};

struct stack
{
	Node* head;
	int length;
};

typedef struct stack Stack;


//Create
STACK stack_create(void)
{
	Stack* pStack = NULL;
	pStack = (Stack*)malloc(sizeof(Stack));
	pStack->head = NULL;
	pStack->length = 0;
	return pStack;
}

//Use
///Adds an item to a stack.
///STACK hStack: The stack to which an item is to be added.
///char data: The character to add to the stack.
///Returns: Success if the add action succeeded, Failure otherwise.
Status stack_push(STACK hStack, char data)
{
	Node* tmp = NULL;
	tmp = (Node*)malloc(sizeof(Node));
	if (tmp == NULL)
	{
		return FAILURE;
	}
	tmp->data = data;
	
	Stack* pStack = (Stack*)hStack;

	tmp->next = pStack->head;
	pStack->head = tmp;
	pStack->length++;

	return SUCCESS;
}

///Removes an item from a stack.
///STACK hStack: The stack from which an item is to be removed.
///Returns: The character removed, '\0' if no such character exists.
char stack_pop(STACK hStack)
{
	if (stack_size(hStack)<=0)
	{
		return '\0';
	}
	Stack* pStack = (Stack*)hStack;
	char value = pStack->head->data;
	Node* tmp = pStack->head->next;
	free(pStack->head);
	pStack->head = tmp;
	pStack->length--;
	return value;
}

///Looks at the top of a stack without removing items.
///STACK hStack: The stack which is to be checked.
///Returns: The character at the top of the stack, '\0' if the stack is empty.
char stack_peek(STACK hStack)
{
	if (stack_size(hStack)<=0)
	{
		return '\0';
	}
	Stack* pStack = (Stack*)hStack;
	return pStack->head->data;
}

///Checks whether there are any items in a stack.
///STACK hStack: The stack to check for items.
///Returns: False if the stack has at least one item, true otherwise.
int stack_size(STACK hStack)
{
	Stack* pStack = (Stack*)hStack;
	return pStack->length;
}

///Prints the entire stack to the console, starting with the top.
///STACK hStack: The stack to print.
void stack_print_all(STACK hStack)
{
	Stack* pStack = (Stack*)hStack;
	Node* tmp = pStack->head;
	while (tmp!=NULL)
	{
		printf("%c", tmp->data);
		tmp = tmp->next;
	}
	printf("\n");
}

//Destroy
///Destroys a stack, freeing all allocated memory.
///STACK* phStack: The Stack to destroy.
void stack_destroy(STACK* phStack) {
	Stack* pStack = (Stack*)* phStack;
	Node* tmp;
	while (pStack->head != NULL) {
		tmp = pStack->head;
		pStack->head = pStack->head->next;
		free(tmp);
	}
	free(pStack);
	*phStack = NULL;
}