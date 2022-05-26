#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "my_string.h"
#include "associative_array.h"
int main(int argc, char* argv[])
{

	
	//Hangman game logic.
	//initialize the words array.
	VECTOR* strings=NULL;
	int num_word_vectors=30;
	strings=(VECTOR*)malloc(sizeof(VECTOR)*num_word_vectors);
	if(strings==NULL)
	{
		return -1;
		
	}
	for(int i=0;i<num_word_vectors;i++)
	{
		strings[i]=vector_init_default();
	}

	//load the words array.
	MY_STRING hMy_string = NULL;
	FILE* fp;
	fp=fopen("dictionary.txt", "r");
	hMy_string=my_string_init_default();
	while(my_string_extraction(hMy_string, fp))
	{
		int length=my_string_get_size(hMy_string);
		vector_push(strings[length],hMy_string);
		hMy_string=my_string_init_default();
	}
	my_string_destroy(&hMy_string);
	hMy_string=NULL;
	fclose(fp);

	//Program logic goes here
	int running = 1;
	while (running > 0)
	{
		//Main loop:
		//>Get a number.
		//>If that number has at least one associated word, clone its word vector and start the game.
		int length = 0;
		MY_STRING guesses = NULL;
		MY_STRING key = NULL;
		VECTOR words = NULL;
		while (length <= 0)
		{
			printf("Please select a word length\n.");
			scanf("%d", length);
			if (length < 0)
			{
				length = 0;
			}
			if (length > 30)
			{
				length = 0;
			}
			if (vector_get_size(strings[length]) > 0)
			{
				guesses = my_string_init_default();
				key = my_string_init_default();
				for (int i = 0; i < length; i++)
				{
					my_string_push_back(key, '-');
				}
				words = vector_init_default();
				int num_words = vector_get_size(strings[length]);
				for (int i = 0; i < num_words; i++)
				{
					vector_push(words, my_string_init_c_string(my_string_c_str(vector_at(strings[length], i))));
				}
			}
		}
		//>Game loop:
		int playing = 1;
		while (playing > 0)
		{
			//>>Take in the player's guess.
			char* guess = NULL;
			while (guess == '\0')
			{
				printf("%s\n", my_string_c_str(key));
				printf("Your guesses so far: %s\n", my_string_c_str(guesses));
				printf("You have %d guesses remaining.\n", 13 - my_string_get_size(guesses));
				printf("Make a new guess. ");
				scanf("%c", guess);

				//Check to see if that character has already been guessed.
				for (int i = 0; i < my_string_get_size(guesses); i++)
				{
					if (tolower(guess) == tolower(my_string_at(guesses,i)))
					{
						printf("You have already guessed that!\n");
						guess = '\0';
						break;
					}
				}

				if (isalpha(guess) < 1)
				{
					printf("That is not a letter!");
					guess = '\0';
				}

			}
			//>>Run the key check on each word in the word vector, and use the associative array to store the words.
			int num_words = vector_get_size(words);
			ASSOCIATIVE_ARRAY key_vects = associative_array_init_length(7);
			for (int i = 0; i < num_words; i++)
			{
				MY_STRING new_key = my_string_init_default();
				get_word_key_value(key, new_key, vector_at(words, i), guess);
				associative_array_add(key_vects, new_key, vector_at(words, i));
			}
			//>>Find the key with the most associated words. If tied, break in favor of the fewest appearances of the guess.
			VECTOR keys = associative_array_get_keys(key_vects);
			int longest_count = 0;
			char* longest_key = NULL;
			for (int i = 0; i < vector_get_size(keys); i++)
			{
				VECTOR test = associative_array_retrieve(key_vects, vector_at(keys, i));
				if (vector_get_size(test) >= longest_count)
				{
					longest_count = vector_get_size(test);
					longest_key = my_string_c_str(vector_at(keys, i));
				}

			}
			vector_destroy(keys);
			//>>Check the key to find out whether the guess was an error.
			int error = 1;
			for (int i = 0; i < length; i++)
			{
				if (tolower(longest_key[i]) == tolower(guess))
				{
					error = 0;
					break;
				}
			}
			if (error > 0)
			{
				my_string_push_back(guesses, guess);
			}
			//>>Clone the new key's vector, and clean up.
			my_string_destroy(key);
			key = my_string_init_c_string(longest_key);
			VECTOR new_words = vector_init_default();
			VECTOR old_words = associative_array_retrieve(key_vects, longest_key);
			for (int i = 0; i < vector_get_size(old_words); i++)
			{
				vector_push(new_words, my_string_init_c_string(my_string_c_str(vector_at(old_words, i))));
			}
			vector_destroy(words);
			words = new_words;
			associative_array_destroy(key_vects);
			//>>Check to see if the game is over:
			//>>>No guesses remain.
			if (my_string_get_size(guesses) >= 13)
			{
				printf("Sorry, you lose! The word was: %s\n", my_string_c_str(vector_at(words,1)));
				playing = 0;
			}
			//>>>The word has been guessed.
			else
			{
				int guessed = 1;
				char* guess_string = my_string_c_str(key);
				for (int i = 0; i < length; i++)
				{
					if (guess_string[i] == '-')
					{
						guessed = 0;
						break;
					}
				}
				if (guessed > 0)
				{
					printf("Congratulations, you win! The word was: %s\n", my_string_c_str(key));
				}
			}
			//>>>If the game is over, clean up.
			if (playing <= 0)
			{
				my_string_destroy(guesses);
				my_string_destroy(key);
				vector_destroy(words);
			}
		}
		//>>Check to see if you should continue playing.
		printf("Play again? Press n to exit.");
		char* replay;
		scanf("%c", replay);
		if (replay == 'n' || replay == 'N')
		{
			running = 0;
		}
	}

	//delete the words array.
	for(int i=0;i<num_word_vectors;i++)
	{
		vector_destroy(strings[i]);
	}
	free(strings);
	//End hangman game logic.
	
	/*
	//String keys test.
	MY_STRING* test=(MY_STRING*)malloc(sizeof(MY_STRING)*4);
	MY_STRING* key=(MY_STRING*)malloc(sizeof(MY_STRING)*4);
	char* guess=(char*)malloc(sizeof(char)*4);

	test[0]=my_string_init_c_string("The");
	key[0]=my_string_init_c_string("---");
	guess[0]='T';

	test[1]=my_string_init_c_string("Truck");
	key[1]=my_string_init_c_string("-----");
	guess[1]='r';

	test[2]=my_string_init_c_string("happy");
	key[2]=my_string_init_c_string("--ppy");
	guess[2]='h';

	test[3]=my_string_init_c_string("awesome");
	key[3]=my_string_init_c_string("--e---e");
	guess[3]='z';

	for(int i=0;i<4;i++)
	{
		printf("Testing %s with key %s and guess %c\n", my_string_c_str(test[i]), my_string_c_str(key[i]), guess[i]);
		get_word_key_value(key[i], key[i], test[i], guess[i]);
		printf("Result: %s\n", my_string_c_str(key[i]));
		my_string_destroy(&(test[i]));
		my_string_destroy(&(key[i]));
	}
	free(test);
	free(key);
	free(guess);
	//End string keys test.
	*/
	
   return 0;
} 
