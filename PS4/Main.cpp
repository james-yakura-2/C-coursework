#include "ED.h"
#include <stdio.h>
#include <cstdio>
#include <iostream>
#include <SFML/System.hpp>

int main()
{
	//Take in first string.
	std::string str1;
	std::getline(std::cin, str1);
	//Take in second string.
	std::string str2;
	std::getline(std::cin, str2);
	//Process strings.
	sf::Clock clock;
	sf::Time t;
	ED distance = ED(str1, str2);
	std::cout << "Minimum cost: " << distance.optDistance() << std::endl;
	std::cout << distance.alignment() << std::endl;
	t = clock.getElapsedTime();
	std::cout << "Execution time is " << t.asSeconds() << "seconds" << std::endl;
}