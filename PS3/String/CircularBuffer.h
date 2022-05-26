/*
* Copyright James Yakura 2020
*/

#pragma once

#include <stddef.h>
#include <stdint.h>
#include <vector>
class CircularBuffer
{
public:
	CircularBuffer(int capacity); // create an empty ring buffer, with given max capacity
	int size(); // return number of items currently in the buffer
	bool isEmpty(); // is the buffer empty (size equals zero)?
	bool isFull(); // is the buffer full (size equals capacity)?
	void enqueue(int16_t x); // add item x to the end
	int16_t dequeue(); // delete and return item from the front
	int16_t peek(); // return (but do not delete) item from the front
};

