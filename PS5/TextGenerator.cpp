/*
* Copyright 2020 James Yakura
*/
#include "MModel.h"
#include <stdio.h>
#include <cstdio>
#include <iostream>

/*
* Takes in a text from the command line, uses it to construct an order-(order) Markov chain, and then outputs (length) characters.
*/
int main(int order, int length)
{
	std::string input=std::string();
	std::cin >> input;
	MModel model = MModel(input, order);
	std::cout << model.generate(input.substr(0, order), length);
}