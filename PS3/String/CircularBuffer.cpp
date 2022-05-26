/*
* Copyright James Yakura 2020
*/

#include "CircularBuffer.h"
#include <stdexcept>

int _capacity;
int _current;
int _size;
int16_t *_contents;

CircularBuffer::CircularBuffer(int capacity)
{
	_capacity = capacity;
	_contents = new int16_t[capacity];
	_current = 0;
	_size = 0;
}

int CircularBuffer::size()
{
	return _size;
}

bool CircularBuffer::isEmpty()
{
	return _size == 0;
}

bool CircularBuffer::isFull()
{
	return _size >= _capacity;
}

void CircularBuffer::enqueue(int16_t x)
{
	if (!isFull())
	{
		_contents[(_current + _size) % _capacity] = x;
		_size++;
	}
	else
	{
		throw std::out_of_range("Buffer full");
	}
}

int16_t CircularBuffer::dequeue()
{
	if (!isEmpty())
	{
		int16_t value = _contents[(_current)];
		_current++;
		if (_current >= _capacity)
		{
			_current = 0;
		}
		_size--;
		return value;
	}
	else
	{
		throw std::out_of_range("Buffer empty");
	}
}

int16_t CircularBuffer::peek()
{
	if (!isEmpty())
	{
		return _contents[_current];
	}
	else
	{
		throw std::out_of_range("Buffer empty");
	}
}

