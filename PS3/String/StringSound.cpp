/*
* Copyright James Yakura 2020
*/

#include "StringSound.h"
#include "CircularBuffer.h"
#include <random>
#include <algorithm>
#include <chrono>

CircularBuffer* buffer;
std::mt19937 seed(time(0));
std::uniform_int_distribution<std::int16_t> rng(-32768,32767);
const double DETERIORATION = .996;
int tic_count = 0;

StringSound::StringSound(double frequency)
{
	buffer = new CircularBuffer(std::ceil(SAMPLES_PER_SEC / frequency));
	while (!(buffer->isFull()))
	{
		buffer->enqueue(0);
	}
}

StringSound::StringSound(std::vector<sf::Int16> init)
{
	buffer = new CircularBuffer(init.size());
	for (unsigned int i = 0; i < init.size(); i++)
	{
		buffer->enqueue(init.at(i));
	}
}

void StringSound::pluck()
{
	//Clear the buffer.
	while (!(buffer->isEmpty()))
	{
		buffer->dequeue();
	}
	//Fill the buffer with random numbers.
	while (!(buffer->isFull()))
	{
		buffer->enqueue(rng(seed));
	}
}

void StringSound::tic()
{
	try
	{
		buffer->enqueue(((double)buffer->dequeue() + (double)buffer->peek()) * .5 * DETERIORATION);
	}
	catch (std::out_of_range)
	{
		//Error message.
	}
	tic_count++;
}

sf::Int16 StringSound::sample()
{
	try
	{
		return buffer->peek();
	}
	catch (std::out_of_range)
	{

	}
	return 0;
}

int StringSound::time()
{
	return tic_count;
}
