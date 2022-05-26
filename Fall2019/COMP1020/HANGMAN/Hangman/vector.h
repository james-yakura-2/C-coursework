#pragma once
#include "generic.h"

//A dynamically-resizing array of items. The current implementation is restricted to my_string for reasons of destructibility.
typedef void* VECTOR;

//Creates a new Vector.
//Param destroy: A method for destroying elements of the Vector.
//Returns: An empty Vector.
VECTOR* vector_init_default();

//Gets the size of a Vector.
//Param hVect: A void pointer to the vector to check.
//Returns: The current number of elements in the Vector.
int vector_get_size(VECTOR hVect);

//Pushes a new element to the vector.
//Param hVect: A void pointer to the vector to recieve the new item.
//Param hItem: A void pointer to the item to be added.
//Returns: 0 or negative if a resize operation failed, 1 or positive otherwise.
int vector_push(VECTOR hVect, Item hItem);

//Gets the vector element at the specified location.
//Param hVect: A void pointer to the vector to check.
//Param index: The array index of the item to retrieve.
//Returns: The item at the specified index.
Item* vector_at(VECTOR hVect, int index);

//Destroys the vector and all of its contents.
//Param hVect: A void pointer to the vector to destroy.
void vector_destroy(VECTOR* hVect);
