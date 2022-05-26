/*
* Copyright 2020 James Yakura
*/
#pragma once

#include <stddef.h>
#include <string>
class ED
{
public:
	const int INSERT_PENALTY = 2;

	ED(std::string str1, std::string str2);

	static int penalty(char ch1, char ch2);

	static int min(int arg1, int arg2, int arg3);

	int optDistance();

	std::string alignment();

	~ED();
};

