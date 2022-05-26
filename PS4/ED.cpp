/*
* Copyright 2020 James Yakura
*/

#include "ED.h"

#include <array>
#include <iostream>

std::string _str1;
std::string _str2;
int** search_array;


ED::ED(std::string str1, std::string str2)
{
	_str1 = str1+' ';
	_str2 = str2+' ';
	search_array = new int*[_str1.size()];
	for (int i = 0; i < _str1.size(); i++)
	{
		search_array[i] = new int[_str2.size()];
		for (int j = 0; j < _str2.size(); j++)
		{
			search_array[i][j] = -1;
		}
	}
}

int ED::penalty(char ch1, char ch2)
{
	if(ch1==ch2)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int ED::min(int arg1, int arg2, int arg3)
{
	if (arg1 <= arg2)
	{
		if (arg1 <= arg3)
		{
			return arg1;
		}
		else
		{
			return arg3;
		}
	}
	else
	{
		if (arg2 <= arg3)
		{
			return arg2;
		}
		else
		{
			return arg3;
		}
	}
}

int ED::optDistance()
{
	if (search_array[0][0] < 0)
	{
		for (int i = int(_str1.size() - 1); i >= 0; i--)
		{
			for (int j = int(_str2.size() - 1); j >= 0; j--)
			{
				if (i == int(_str1.size()-1) && int(j == _str2.size()-1))
				{
					search_array[i][j] = int(0);
				}
				else
				{
					int below_move;
					if (i >= _str1.size() - 1)
					{
						below_move = INT16_MAX;
					}
					else
					{
						below_move = search_array[i + 1][j]+INSERT_PENALTY;
					}
					int right_move;
					if (j >= _str2.size() - 1)
					{
						right_move = INT16_MAX;
					}
					else
					{
						right_move = search_array[i][j + 1]+INSERT_PENALTY;
					}
					int diagonal_move;
					if (i >= _str1.size()-1 || j >= _str2.size()-1)
					{
						diagonal_move = INT16_MAX;
					}
					else
					{
						diagonal_move = search_array[i + 1][j + 1] + penalty(_str1.at(i), _str2.at(j));
					}
					search_array[i][j] = min(below_move, right_move, diagonal_move);	
				}
			}
		}
	}




	return search_array[0][0];
}

std::string ED::alignment()
{
	int i = 0;
	int j = 0;
	std::string value = "";
	if (search_array[0][0] < 0)
	{
		optDistance();
	}
	while (i < _str1.size() && j < _str2.size())
	{
		if (i != _str1.size() - 1 || j != _str2.size() - 1)
		{
			//Can the next space be reached by a diagonal move?
			int checking_val;
			if (i >= _str1.size() - 1 || j >= _str2.size() - 1)
			{
				checking_val = INT32_MAX;
			}
			else
			{
				checking_val = search_array[i + 1][j + 1] + penalty(_str1.at(i), _str2.at(j));
			}
			if (checking_val == search_array[i][j])
			{
				value.append(1, _str1.at(i));
				value.append(" ");
				value.append(1, _str2.at(j));
				value.append(" ");
				value.append("" + penalty(_str1.at(i), _str2.at(j)));
				value.append("\n");

				i++;
				j++;
			}
			//Can the next space be reached by a downward move?
			else
			{
				if (i >= _str1.size() - 1)
				{
					checking_val = INT32_MAX;
				}
				else
				{
					checking_val = search_array[i + 1][j] + INSERT_PENALTY;
				}
				if (search_array[i][j] == checking_val)
				{
					value.append(1, _str1.at(i));
					value.append(" - ");
					value.append("" + INSERT_PENALTY);
					value.append("\n");
					i++;
				}
				//If you reach this point and the search array is valid, the move is horizontal.
				else
				{
					value.append("- ");
					value.append(1, _str2.at(j));
					value.append(" ");
					value.append("" + INSERT_PENALTY);
					value.append("\n");

					j++;
				}
			}
		}
		else
		{
			i++;
			j++;
		}
	}
	return value;
}

ED::~ED()
{
	for (int i = 0; i < _str1.size(); i++)
	{
		delete[] search_array[i];
	}
	delete [] search_array;
}
