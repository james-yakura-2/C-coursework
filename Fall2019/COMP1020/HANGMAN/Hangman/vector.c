#include "vector.h"
#include "my_string.h"
#include <stddef.h>
#include <stdlib.h>

struct vector
{
	int size;
	int capacity;
	Item* data;
	
};

typedef struct vector Vector;

//Creates a new Vector.
//Param destroy: A method for destroying elements of the Vector.
//Returns: An empty Vector.
VECTOR* vector_init_default()
{
	Vector* vect=NULL;
	vect=(Vector*)malloc(sizeof(Vector));
	if(vect!=NULL)
	{
		vect->size=0;
		vect->capacity=2;
		vect->data=NULL;
		vect->data=(Item*)malloc(sizeof(Item)*vect->capacity);
		if(vect->data==NULL)
		{
			free(vect);
		}
	}
	return vect;
}

//Gets the size of a Vector.
//Param hVect: A void pointer to the vector to check.
//Returns: The current number of elements in the Vector.
int vector_get_size(VECTOR hVect)
{
	return ((Vector*)hVect)->size;
}

//Pushes a new element to the vector.
//Param hVect: A void pointer to the vector to recieve the new item.
//Param hItem: A void pointer to the item to be added.
//Returns: 0 or negative if a resize operation failed, 1 or positive otherwise.
int vector_push(VECTOR hVect, Item hItem)
{
	Vector* pVect=(Vector*)hVect;
	//printf("Writing to position %d, current capacity %d\n",pVect->size,pVect->capacity);//Debug code.
	if(pVect->size>=pVect->capacity)
	{
		
		int new_capacity=pVect->size*2;
		Item* new_data=NULL;
		new_data=(Item*)malloc(sizeof(Item)*new_capacity);
		if(new_data==NULL)
		{
			return 0;
		}
		for(int i=0;i<pVect->capacity;i++)
		{
			new_data[i]=pVect->data[i];
		}
		free(pVect->data);
		pVect->data=new_data;
		pVect->capacity=new_capacity;
	}
	pVect->data[pVect->size]=hItem;
	pVect->size++;
}

//Gets the vector element at the specified location.
//Param hVect: A void pointer to the vector to check.
//Param index: The array index of the item to retrieve.
//Returns: The item at the specified index.
Item* vector_at(VECTOR hVect, int index)
{
	Vector* pVect=(Vector*)hVect;
	return pVect->data[index];
}

//Destroys the vector and all of its contents.
//Param hVect: A void pointer to the vector to destroy.
void vector_destroy(VECTOR* hVect)
{
	Vector* pVect=(Vector*)hVect;
	//printf("Deleting %d words.\n", pVect->size);//Debug code.
	for(int i=0;i<pVect->size;i++)
	{
		//printf("Deleting %s\n", my_string_c_str(pVect->data[i]));//Debug code.
		my_string_destroy(&(pVect->data[i]));
	}
	free(pVect->data);
	free(hVect);
}
