/**********************************************************************
Program: Daily 7
Author: James Yakura
Date: 10/8
Time spent: 5:00
Purpose: The purpose of this program is to verify a series of characters to determine that open characters ('(', '[', '{') are paired with the appropriate close characters (')', ']', '}').
Note: Online Judge was returning a 500 error page when I finished.
***********************************************************************/

#include "Stack.h";
#include <stdio.h>;

int main(char* args, int argl)
{
	//Get the number of lines. This should be the first line.
	int num_lines;
	scanf_s("%d", &num_lines);
	char chr;
	do
	{
		chr = fgetc(stdin);
	} while (chr != '\n');
	//For each line,
	for (int i = 0; i < num_lines; i++)
	{
		Boolean running = TRUE;
		Boolean pass = TRUE;
		STACK* char_stack = stack_create();
		//>use the stack to verify the character string.
		while (running == TRUE)
		{
			chr = fgetc(stdin);
			//printf("Read:%c\n",chr);//Debug code.
			switch (chr)
			{
			case '(':
				stack_push(char_stack, chr);
				break;
			case '[':
				stack_push(char_stack, chr);
				break;
			case '{':
				stack_push(char_stack, chr);
				break;
			case ')':
				if (stack_size(char_stack)<=0 || stack_pop(char_stack) != '(')
				{
					pass = FALSE;
				}
				break;
			case ']':
				if (stack_size(char_stack) <= 0 || stack_pop(char_stack) != '[')
				{
					pass = FALSE;
				}
				break;
			case '}':
				if (stack_size(char_stack) <= 0 || stack_pop(char_stack) != '{')
				{
					pass = FALSE;
				}
				break;
			case '\n':
				if (stack_size(char_stack) > 0)
				{
					pass = FALSE;
				}
				running = FALSE;
				break;
			default:
				pass = FALSE;
				break;
			}
		}
		//printf("Stack(%i):", stack_size(char_stack)); stack_print_all(char_stack);//Debug code.
		if (pass == TRUE)
		{
			printf("Yes\n");
		}
		else
		{
			printf("No\n");
		}
		stack_destroy(&char_stack);

	}
}