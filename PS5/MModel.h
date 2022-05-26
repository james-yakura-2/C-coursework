/*
* Copyright 2020 James Yakura.
*/
#pragma once

#include <stddef.h>
#include <string>
#include <stdio.h>

class MModel
{
public:

	// create a Markov model of order k from given text
	MModel(std::string text, int k); // Assume that text has length at least k.
		
	int kOrder(); // order k of Markov model
	
	// number of occurrences of kgram in text
	int freq(std::string kgram); // (throw an exception if kgram is not of length k)

	// number of times that character c follows kgram
	// if order=0, return num of times char c appears
	// (throw an exception if kgram is not of length k)
	int freq(std::string kgram, char c);

	// random character following given kgram
	// (Throw an exception if kgram is not of length k.
	// Throw an exception if no such kgram.)
	char kRand(std::string kgram);
	
	// generate a string of length L characters
	// by simulating a trajectory through the corresponding
	// Markov chain. The first k characters of the newly
	// generated string should be the argument kgram.
	// Throw an exception if kgram is not of length k.
	// Assume that L is at least k.
	std::string generate(std::string kgram, int L);

	std::ostream& operator<<(std::ostream& ostream);
	// overload the stream insertion operator and display
	// the internal state of the Markov Model. Print out
	// the order, the alphabet, and the frequencies of
	// the k-grams and k+1-grams.
};

