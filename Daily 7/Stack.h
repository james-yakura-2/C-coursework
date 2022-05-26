#pragma once
#include <stdio.h>
enum status
{
	FAILURE,
	SUCCESS
};

enum boolean
{
	FALSE,
	TRUE
};

typedef void* STACK;
typedef enum status Status;
typedef enum boolean Boolean;


//Create
STACK stack_create(void);

//Use
///Adds an item to a stack.
///STACK hStack: The stack to which an item is to be added.
///char data: The character to add to the stack.
///Returns: Success if the add action succeeded, Failure otherwise.
Status stack_push(STACK, char);

///Removes an item from a stack.
///STACK hStack: The stack from which an item is to be removed.
///Returns: The character removed, '\0' if no such character exists.
char stack_pop(STACK);

///Looks at the top of a stack without removing items.
///STACK hStack: The stack which is to be checked.
///Returns: The character at the top of the stack, '\0' if the stack is empty.
char stack_peek(STACK);

///Checks whether there are any items in a stack.
///STACK hStack: The stack to check for items.
///Returns: The number of items in the stack
int stack_size(STACK);

///Prints the entire stack to the console, starting with the top.
///STACK hStack: The stack to print.
void stack_print_all(STACK);

//Destroy
///Destroys a stack, freeing all allocated memory.
///STACK* phStack: The Stack to destroy.
void stack_destroy(STACK*);