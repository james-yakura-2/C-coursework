/**********************************************************************
Program: Daily 8
Author: James Yakura
Date: <date you finish the program>
Time spent: 4:00
Purpose: The purpose of this program is to implement a priority queue using a heap.
***********************************************************************/
//Assumption: Priority queue should output elements in FIFO order within priority levels. 
//To maintain memory of insertion order, the priority queue tags each element with both priority and a sequence number.
#include "priority_queue.h"
#include <stddef.h>
#include <stdio.h>


struct priority_pair
{
	int data;
	int seq_added;
	int priority;
};

typedef struct priority_pair Priority_Pair;

void priority_pair_destroy(Priority_Pair* pPair);

int compare(Priority_Pair* left, Priority_Pair* right);

struct priority_queue
{
	int capacity;
	int size;
	int num_added;
	Priority_Pair** data;
};

typedef struct priority_queue Priority_Queue;

void heapify(Priority_Queue* queue, int index);

//Precondition: Creates an empty priority queue that can store integer data items 
//   with different integer priority.  Higher
//   integer values indicate higher priority in the queue.  For example, consider the 
//   priority and the data value to be key-value pairs where the priority is the key
//   and the data is the value.  The queue could hold 21,10 and 35, 5 so that the
//   first item to be removed from the queue would be the data value 5 because 
//   it has higher priority (35) than the data value 10 which only has (21).
//Postcondition:  Returns the handle to an empty priority queue.
PRIORITY_QUEUE priority_queue_init_default(void)
{
	Priority_Queue* queue = NULL;
	queue = (Priority_Queue*)malloc(sizeof(Priority_Queue));
	if (queue != NULL)
	{
		queue->capacity = 1;
		queue->size = 0;
		queue->data = NULL;
		queue->num_added = 0;
		queue->data = (Priority_Pair**)malloc(sizeof(Priority_Pair*) * queue->capacity);
		if (queue->data == NULL)
		{
			free(queue);
			queue = NULL;
		}
		queue->data[0] = NULL;
	}

	return queue;
}

//Precondition: hQueue is a handle to a valid priority queue opaque object. 
//   Higher priority_level values indicate higher priority in the queue.
//   data_item is simply a value we are storing in the queue.
//Postcondition: returns SUCCESS if the item was successfully added to the queue
//   and FAILURE otherwise.
Status priority_queue_insert(PRIORITY_QUEUE hQueue, int priority_level, int data_item)
{
	//Create the priority pair.
	Priority_Pair* pair = NULL;
	pair = (Priority_Pair*)malloc(sizeof(Priority_Pair));
	if (pair == NULL)
	{
		return FAILURE;
	}
	pair->priority = priority_level;
	pair->data = data_item;
	//Resize if necessary.
	Priority_Queue* pQueue = (Priority_Queue*)hQueue;
	pair->seq_added = pQueue->num_added;
	pQueue->num_added++;
	if (pQueue->size >= pQueue->capacity)
	{
		int new_capacity = pQueue->capacity * 2;
		Priority_Pair** new_data = NULL;
		new_data = (Priority_Pair**)malloc(sizeof(Priority_Pair*) * new_capacity);
		if (new_data == NULL)
		{
			free(pair);
			return FAILURE;
		}

		//Clean up the newly-allocated data.
		for (int i = 0; i < new_capacity; i++)
		{
			new_data[i] = NULL;
		}

		//Transfer all items into the new data. All items must be transfered in order to prevent memory leaks.
		for (int i = 0; i < pQueue->capacity; i++)
		{
			new_data[i] = pQueue->data[i];
		}

		pQueue->data = new_data;
		pQueue->capacity = new_capacity;
	}
	if (pQueue->data[pQueue->size] != NULL)
	{
		priority_pair_destroy(pQueue->data[pQueue->size]);
	}
	pQueue->data[pQueue->size] = pair;
	pQueue->size++;
	heapify(pQueue, pQueue->size - 1);
	//printf("Size: %d. Capacity: %d\n", pQueue->size, pQueue->capacity);//Debug code.
	return SUCCESS;
}

//Precondition: hQueue is a handle to a valid priority queue opaque object. 
//Postcondition: returns SUCCESS if the highest priority item was removed from the queue 
//   and FAILURE if the queue was empty.
Status priority_queue_service(PRIORITY_QUEUE hQueue)
{
	Priority_Queue* pQueue = (Priority_Queue*)hQueue;
	if (pQueue->size == 0)
	{
		return FAILURE;
	}
	priority_pair_destroy(pQueue->data[0]);
	pQueue->data[0] = pQueue->data[pQueue->size-1];
	pQueue->data[pQueue->size-1] = NULL;
	pQueue->size--;
	heapify(pQueue, 0);
	//printf("Size: %d. Capacity: %d.\n", pQueue->size, pQueue->capacity);//Debug code.
	return SUCCESS;
}

//Precondition: hQueue is a handle to a valid priority queue opaque object. 
//Postcondition: returns a copy of the data value for the
//   highest priority item in the queue.  Sets the variable at the address 
//   referred to in pStatus to SUCCESS if there is
//   at least one item in the queue and FAILURE otherwise.  If pStatus is
//   passed in as NULL then the status value is ignored for this run of the
//   function.
int priority_queue_front(PRIORITY_QUEUE hQueue, Status* pStatus)
{
	Priority_Queue* pQueue = (Priority_Queue*)hQueue;
	if (pQueue->size == 0)
	{
		if (pStatus != NULL)
		{
			*pStatus = FAILURE;
		}
		return 0;
	}
	else
	{
		if (pStatus != NULL)
		{
			*pStatus = SUCCESS;
		}
		return pQueue->data[0]->data;
	}
}

//Precondition: hQueue is a handle to a valid priority queue opaque object. 
//Postcondition: returns TRUE if the priority_queue is empty and FALSE otherwise.
Boolean priority_queue_is_empty(PRIORITY_QUEUE hQueue)
{
	if (((Priority_Queue*)hQueue)->size == 0)
	{
		return TRUE;
	}
	return FALSE;
}

//Precondition: phQueue is a pointer to the handle of a valid priority queue opaque object.
//Postcondition: The opaque object will be free'd from memory and the handle pointed to
//   by phQueue will be set to NULL.
void priority_queue_destroy(PRIORITY_QUEUE* phQueue)
{
	//There is something seriously wrong here. Size and capacity do not match last observed value.
	Priority_Queue* pQueue = (Priority_Queue*)phQueue;
	//printf("Deleting queue of size %d and capacity %d\n", pQueue->size, pQueue->capacity);//Debug code
	for (int i = 0; i < pQueue->capacity; i++)
	{
		if (pQueue->data[i] != NULL)
		{
			//printf("Freeing position %d\n", i);//Debug code.
			priority_pair_destroy(pQueue->data[i]);
		}
	}
	free(pQueue->data);
	//printf("Data freed.");//Debug code
	free(pQueue);
	*phQueue = NULL;
}

//Recursively applies the max-heap property to the queue's data.
//Note: This will only partially heapify data that was not in a max-heap before the element at index was changed.
void heapify(Priority_Queue* queue, int index)
{
	/*//Debug code.
	for (int i = 0; i < queue->size; i++)
	{
		printf("%d ", queue->data[i]->data);
	}
	printf("\nHeapifying position %d\n", index);
	//End debug code.*/

	//Children are index*2+1, index*2+2. Special case: child does not exist (has index greater than queue size)
	//Parent is cieling(index/2)-1. Special case: index is top node and has no parent (index=0)
	//compare to children, swap with largest child if either child is greater, heapify swapped child
	int child_swap_index = -1;
	int left_child_index = index * 2 + 1;
	int right_child_index = index * 2 + 2;
	int parent_index = (index - 1) / 2;
	//printf("Self: %d\n", queue->data[index]->data);//Debug code

	if (left_child_index < queue->size)
	{
		//printf("Left child: %d\n", queue->data[index]->data);//Debug code
		if (compare(queue->data[index], queue->data[left_child_index])>0)
		{
			child_swap_index = left_child_index;
		}
		if (right_child_index < queue->size)
		{
			//printf("Right child: %d\n", queue->data[index]->data);
			if (compare(queue->data[index], queue->data[right_child_index])>0)
			{
				if (compare(queue->data[left_child_index], queue->data[right_child_index])>0)
				{
					child_swap_index = right_child_index;
				}
			}
		}
	}
	if (child_swap_index >= 0)
	{
		Priority_Pair* swap = queue->data[child_swap_index];
		queue->data[child_swap_index] = queue->data[index];
		queue->data[index] = swap;
		heapify(queue, child_swap_index);
	}
	//heapify parent if parent exists
	if (index > 0)
	{
		heapify(queue, parent_index);
	}
}

//Returns negative if left is higher priority than right, positive if right is higher priority than left.
int compare(Priority_Pair* left, Priority_Pair* right)
{
	if (left->priority != right->priority)
	{
		return (right->priority) - (left->priority);
	}
	return (left->seq_added) - (right->seq_added);
}

void priority_pair_destroy(Priority_Pair* pPair)
{
	free(pPair);
	pPair = NULL;
}