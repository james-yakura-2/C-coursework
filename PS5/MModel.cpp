/*
* Copyright 2020 James Yakura
*/

#include "MModel.h"

#include <map>
#include <random>
#include <queue>
#include <stdio.h>
#include <cstdio>
#include <iostream>
#include <exception>

std::mt19937 rng = std::mt19937(rand());

std::map<std::string, std::map<char, int>> nextChar;

int order;

MModel::MModel(std::string text, int k)
{
	order = k;
	//Iterate over text, adding it to the model.
	for (int i = 0; i < text.size() - 1; i++)
	{
		char* key = new char[k];
		for (int j = 0; j < k; j++)
		{
			key[j] = text.at((i + j) % text.size());
		}
		insert(std::string(key), text.at((i + k) % text.size()));
	}
}

int MModel::kOrder()
{
	return order;
}

int MModel::freq(std::string kgram)
{
	//Search for the specified kgram.
	//If found, return the sum of all next frequencies for that kgram.
	//Otherwise, return 0.
	for (auto const iter1 : nextChar)
	{
		if (iter1.first.compare(kgram) == 0)
		{
			int total=0;
			for (auto const iter2 : iter1.second)
			{
				total += iter2.second;
			}
			return total;
		}
	}
	return 0;
}

int MModel::freq(std::string kgram, char c)
{
	//Search for the specified kgram.
	//If found, look up the specified character in that kgram's frequency table.
	//If either is not found, return 0.
	for (auto const iter1 : nextChar)
	{
		if (iter1.first.compare(kgram)==0)
		{
			auto loc = iter1.second.find(c);
			if (loc != iter1.second.end())
			{
				return loc[c];
			}
			return 0;
		}
	}
	return 0;
}

char MModel::kRand(std::string kgram)
{
	int roll = std::uniform_int_distribution<int>(0, freq(kgram))(rng);
	int total = 0;
	for (auto const& iter : nextChar[kgram])
	{
		total += iter.second;
		if (roll <= total)
		{
			return iter.first;
		}
	}
	throw std::logic_error("Cannot find a next value for the current k-gram.");
}

std::string MModel::generate(std::string kgram, int L)
{
	std::string result=std::string();
	char* current = new char[kgram.size()];
	for (int i = 0; i < kgram.size(); i++)
	{
		current[i] = kgram.at(i);
	}
	for (int i = 0; i < L; i++)
	{
		char next = kRand(std::string(current));
		for (int j = 0; j < kgram.size() - 1; j++)
		{
			current[j] = current[j + 1];
		}
		current[kgram.size() - 1] = next;
		result.push_back(next);
	}
	return result;
}

std::ostream& MModel::operator<<(std::ostream& out)
{
	out << "Order: " << order << std::endl;
	out << "k-grams: " << std::endl;
	std::map<char, int> charsDisplayed = std::map<char,int>();
	for (auto const iter : nextChar)
	{
		out << iter.first << ":" << freq(iter.first) << std::endl;
	}
	out << "k+1-grams:" << std::endl;
	for (auto const iter : nextChar)
	{
		for (auto const iter2 : iter.second)
		{
			out << iter.first << iter2.first << ":" << iter2.second << std::endl;
			if (charsDisplayed.find(iter2.first) == charsDisplayed.end())
			{
				charsDisplayed[iter2.first] = 1;
			}
			else
			{
				charsDisplayed[iter2.first]++;
			}
		}
	}
	out << "Alphabet: " << std::endl;
	for (auto const iter : charsDisplayed)
	{
		out << iter.first << ":" << iter.second << std::endl;
	}
	return out;
}

void insert(std::string key, char value)
{
	//Search for the specified key. If found:
	//Search the key's frequency table for the value. If found, increment it. Otherwise, insert 1.
	std::map<char,int> freqTable;
	bool keyFound = false;
	for (auto const iter : nextChar)
	{
		if (iter.first.compare(key) == 0)
		{
			freqTable = iter.second;
			keyFound = true;
		}
	}
	if (!keyFound)
	{
		freqTable = std::map<char, int>();
		nextChar[key] = freqTable;
	}
	auto loc = freqTable.find(value);
	if (loc == freqTable.end())
	{
		freqTable[value] = 0;
	}
	else
	{
		freqTable[value]++;
	}
}