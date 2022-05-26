/*
* Copyright James Yakura 2020
*/

#pragma once
#include <stddef.h>
#include <vector>
#include <SFML/Audio.hpp>
#include <SFML/Config.hpp>
#include <SFML/Audio/AlResource.hpp>


class StringSound
{
public:

	static const int SAMPLES_PER_SEC = 44100;

	/*
	* create a guitar string sound of the given frequency using a sampling rate of 44,100
	*/
	StringSound(double frequency);

	/*
	* create a guitar string with size and initial values are given by the vector
	*/
	StringSound(std::vector<sf::Int16> init);

	/*
	* pluck the guitar string by replacing the buffer with random values, representing white noise
	*/
	void pluck();

	/*
	* advance the simulation one time step
	*/
	void tic();

	/*
	* return the current sample
	*/
	sf::Int16 sample();

	/*
	* return number of times tic was called so far
	*/
	int time();
};

