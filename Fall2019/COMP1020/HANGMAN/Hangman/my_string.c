#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h>
#include "my_string.h"

struct my_string
{
int capacity;
int size;
char* data;
};

typedef struct my_string My_String;

Status my_string_resize(My_String*, int);

MY_STRING my_string_init_default(void)
{
	My_String* str=NULL;
	//printf("Allocate memory for string.\n");
	str=(My_String*)malloc(sizeof(My_String));
	if(str!=NULL)
	{
		str->capacity=1;
		str->size=0;
		//printf("Allocate memory for string data.\n");
		str->data=(char*)malloc(sizeof(char)*str->capacity);
		//printf("Attempted allocation.\n");
		if(str->data == NULL)
		{
			free(str);
			str=NULL;
			//printf("String data allocation failed.\n");
		}
		else
		{
			//printf("Memory for string data allocated successfully.\n");
		}
	}
	return str;
}

//Precondtion: c_string is a valid null terminated c-string.
//Postcondition: Allocate space for a string object that represents a string
//   with the same value as the given c-string.  The capacity of the string
//   object will be set to be one greater than is required to hold the string.
//   As an example, the string "the" would set capacity at 4 instead of 3. A
//   copy of the address of the opaque object will be returned on success and
//   NULL on failure.
MY_STRING my_string_init_c_string(const char* c_string)
{
	My_String* str=NULL;
	//Find the required length.
	int length=0;
	for(length=0;c_string[length]!='\0';length++) {}
	length++;
	//printf("Capacity: %d\n", length);//Debug code.
	//Allocate memory.
	str=(My_String*)malloc(sizeof(My_String));
	if(str!=NULL)
	{
		str->capacity=length;
		str->size=length-1;
		str->data=(char*)malloc(sizeof(char)*str->capacity);
		if(str->data == NULL)
		{
			free(str);
			str=NULL;
		}
		else
		{
			for(int i=0;i<length;i++)
			{
				//printf("%cS\n", c_string[i]);//Debug code.
				str->data[i]=c_string[i];
			}
		}
	}
	return str;
}


//Precondition: hMy_string is the handle of a valid My_string object.
//Postcondtion: Returns a copy of the integer value of the object's capacity.
int my_string_get_capacity(MY_STRING hMy_string)
{
	return ((My_String*)hMy_string)->capacity;
}

//Precondition: hMy_string is the handle of a valid My_string object.
//Postcondtion: Returns a copy of the integer value of the object's size.
int my_string_get_size(MY_STRING hMy_string)
{
	return ((My_String*)hMy_string)->size;
}

//Precondition: hLeft_string and hRight_string are valid My_string objects.
//Postcondition: returns an integer less than zero if the string represented by hLeft_string is lexicographically smaller than hRight_string.  If one string is a prefix of the other string then the shorter string is considered to be the smaller one. (app is less than apple).  Returns 0 if the strings are the same and returns a number greater than zero if the string represented by hLeft_string is bigger than hRight_string.
int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string)
{
	My_String* pLeft_string=(My_String*)hLeft_string;
	My_String* pRight_string=(My_String*)hRight_string;

	int left_size=pLeft_string->size;
	int right_size=pRight_string->size;

	return left_size-right_size;
}

//Precondition: hMy_string is the handle to a valid My_string object.
//Postcondition: hMy_string will be the handle of a string object that contains the next string from the file stream fp according to the following rules. 1) Leading whitespace will be ignored. 2) All characters (after the first non-whitespace character is obtained and included) will be added to the string until a stopping condition is met.  The capacity of the string will continue to grow as needed until all characters are stored. 3) A stopping condition is met if we read a whitespace character after we have read at least one non-whitespace character or if we reach the end of the file. Function will return SUCCESS if a non-empty string is read successfully. and failure otherwise.  Remember that the incoming string may aleady contain some data and this function should replace the data but not necessarily resize the array unless needed.
Status my_string_extraction(MY_STRING hMy_string, FILE* fp)
{
	My_String* pMy_string=(My_String*)hMy_string;
	pMy_string->size=0;
	
	//Ignore leading whitespace.
	char buffer[1];
	do
	{
		int elements_read=fread(buffer, 1, 1, fp);
		if(elements_read<1)
		{
			return FAILURE;
		}
		//printf("%c\n",buffer[0]);//Debug code.
	}
	while (isspace(buffer[0]));
	
	//Read until whitespace reached.

	fpos_t position;
	for(int i=0;!isspace(buffer[0]);i++)
	{
		fgetpos(fp, &position);
		//Check capacity to ensure there is room to write.
		if(pMy_string->capacity<=i)
		{
			if(my_string_resize(pMy_string, pMy_string->capacity*2)==FAILURE)
				return FAILURE;			
		}
		//Copy the buffer to the string.
		pMy_string->data[i]=buffer[0];
		//printf("Array contents:%s\n",pMy_string->data);//Debug code.
		pMy_string->size++;
		//Read the next character into the buffer.
		int elements_read=fread(buffer, 1, 1, fp);
		if(elements_read<1)
		{
			buffer[0]=' ';
		}
		//printf("%c\n",buffer[0]);//Debug code.

	}
	fsetpos(fp, &position);
	//printf("%s",pMy_string->data);//Debug code.
	//printf("%s\n",pMy_string->data);//Debug code.
	return SUCCESS;
}

//Precondition: hMy_string is the handle to a valid My_string object.
//Postcondition: Writes the characters contained in the string object indicated by the handle hMy_string to the file stream fp. Function will return SUCCESS if it successfully writes the string and FAILURE otherwise.
Status my_string_insertion(MY_STRING hMy_string, FILE* fp)
{
	My_String* pMy_string=(My_String*)hMy_string;
	//printf("Printing:%s\n",pMy_string->data);//Debug code.
	int chars_written=fwrite(pMy_string->data, 1, pMy_string->size, fp);
	return chars_written >= pMy_string->size;
}

//Precondition: hMy_string is the handle to a valid My_string object.
//Postcondition: If successful, places the character item at the end of the string and returns SUCCESS.  If the string does not have enough room and cannot resize to accomodate the new character then the operation fails and FAILURE is returned.  The resize operation will attempt to amortize the cost of a resize by making the string capacity somewhat larger than it was before (up to 2 times bigger). 
Status my_string_push_back(MY_STRING hMy_string, char item)
{
	My_String* pMy_string=(My_String*)hMy_string;
	//If the string is at capacity, double its length.
	if(pMy_string->size>=pMy_string->capacity)
	{
		if(my_string_resize(pMy_string, pMy_string->capacity*2)==FAILURE)
			return FAILURE;
	}
	//Add the character and increment size.
	pMy_string->data[pMy_string->size]=item;
	pMy_string->size++;
	return SUCCESS;
}

//Precondition: hMy_string is the handle to a valid My_string object.
//Postcondition: Removes the last character of a string in constant time.
//Guaranteed to not cause a resize operation of the internal data.  Returns SUCCESS on success and FAILURE if the string is empty.
Status my_string_pop_back(MY_STRING hMy_string)
{
	My_String* pMy_string=(My_String*)hMy_string;
	if(pMy_string->size<=0)
	{
		return FAILURE;
	}
	pMy_string->size--;
	return SUCCESS;
}

//Precondition: hMy_string is the handle to a valid My_string object.
//Postcondition:  Returns the address of the character located at the given index if the index is in bounds but otherwise returns NULL.  This address is not usable as a c-string since the data is not NULL terminated and is intended to just provide access to the element at that index.
char* my_string_at(MY_STRING hMy_string, int index)
{
	My_String* pMy_string=(My_String*)hMy_string;
	if(index<0 || index>=pMy_string->size)
	{
		return NULL;
	}
	return &(pMy_string->data[index]);
}

//Precondition: hMy_string is the handle to a valid My_string object.
//Postcondition: Returns the address of the first element of the string object for use as a c-string.  The resulting c-string is guaranteed to be NULL terminated and the memory is still maintained by the string object though the NULL is not actually counted as part of the string (in size).
char* my_string_c_str(MY_STRING hMy_string)
{
	My_String* pMy_string=(My_String*)hMy_string;
	//Resize if necessary, adding one position.
	if(pMy_string->size>=pMy_string->capacity)
	{
		if(my_string_resize(pMy_string, pMy_string->capacity+1)==FAILURE)
		{
			return (char)NULL;
		};
	}
	//Add a null terminator.
	pMy_string->data[pMy_string->size]=(char)NULL;
	//Return the data array.
	return pMy_string->data;
}

//Resizes the string. This method will produce an error if the new capacity is less than the current size.
//My_String* pMy_string: The My_string to resize.
//int new_capacity: The new capacity of the string.
Status my_string_resize(My_String* pMy_string, int new_capacity)
{
	//Allocate memory.
	char* new_data=NULL;
	new_data=(char*)malloc(sizeof(char)*new_capacity);
	if(new_data==NULL)
	{
		return FAILURE;
	}
	//Copy data to the new string.
	for(int i=0;i<pMy_string->size;i++)
	{
		new_data[i]=pMy_string->data[i];
	}
	free(pMy_string->data);
	pMy_string->data=new_data;
	pMy_string->capacity=new_capacity;
	return SUCCESS;
}

//Precondition: hResult and hAppend are handles to valid My_string objects.
//Postcondition:  hResult is the handle of a string that contains the original hResult object followed by the hAppend object concatenated together. This function should guarantee no change to the hAppend object and return SUCCESS if they operation is successful and FAILURE if the hResult object is unable to accomodate the characters in the hAppend string perhaps because of a failed resize operation.  On FAILURE, no change to either string should be made.
Status my_string_concat(MY_STRING hResult, MY_STRING hAppend)
{
	My_String* pResult=(My_String*)hResult;
	My_String* pAppend=(My_String*)hAppend;
	
	//Check to see if the result has enough space.
	int new_size=pResult->size+pAppend->size;
	if(pResult->capacity < new_size)
	{
		if(my_string_resize(pResult, new_size)==FAILURE)
			return FAILURE;
	}
	//Append the strings.
	for(int i=0;i<pAppend->size;i++)
	{
		pResult->data[pResult->size+i]=pAppend->data[i];
	}
	pResult->size=new_size;
	return SUCCESS;
}

//Precondition: hMy_string is the handle to a valid My_string object.
//Postcondition: Returns an enumerated type with value TRUE if the string is empty and FALSE otherwise.
Boolean my_string_empty(MY_STRING hMy_string)
{
	My_String* pMy_string=(My_String*)hMy_string;
	if(pMy_string->size<=0)
		return TRUE;
	return FALSE;
}

//Precondition: pLeft is the address of a MY_STRING handle containing a valid MY_STRING object address OR NULL. The value of Right must be the handle of a valid MY_STRING object
//Postcondition:  On Success pLeft will contain the address of a handle to a valid MY_STRING object that is a deep copy of the object indicated by Right.  If the value of the handle at the address indicated by pLeft is originally NULL then the function will attempt to initialize a new object that is a deep copy of the object indicated by Right, otherwise the object indicated by the handle at the address pLeft will attempt to resize to hold the data in Right.  On failure pLeft will be left as NULL and any memory that may have been used by a potential object indicated by pLeft will be returned to the freestore. 
void my_string_assignment(Item* pLeft, Item Right)
{
	My_String* right=(My_String*)Right;
	My_String* left=NULL;
	if(*pLeft==NULL)
	{
		left=(My_String*)malloc(sizeof(My_String));
		*pLeft=left;
	}
	else
	{
		left=(My_String*)*pLeft;
		free(left->data);
	}
	if(left!=NULL)
	{
		left->size=right->size;
		left->capacity=right->capacity;
		left->data=NULL;
		left->data=malloc(sizeof(char)*left->capacity);
		if(left->data==NULL)
		{
			free(left);
			*pLeft=NULL;
		}
		else
		{
			for(int i=0;i<left->size;i++)
			{
				left->data[i]=right->data[i];
			}
		}
	}
}

//Precondition: current_word_family, new_key, and word are all handles to valid MY_STRING opaque objects. guess is an alphabetical characer that can be either upper or lower case.
//Postcondition: Returns SUCCESS after replacing the string in new_key with the key value formed by considering the current word family, the word, and the guess. Returns failure in the case of a resizing problem with the new key string.
//Note: A dash ('-') will be used to represent a blank. Assume that no words in the dictionary contain dashes.
//Note: This function will not correct the key if the word is not part of the current family. For example, if the word is "happy", the key is "a----", and the guess is 'y', the new key will be "a---y". The exception is if the guess would replace a letter; if the guess had been 'h', the new key would be "h----".
//Note: This function assumes that current_word_family and word are the same length.
Status get_word_key_value(MY_STRING current_word_family, MY_STRING new_key, MY_STRING word, char guess)
{
	My_String* pCurrent_family=(My_String*)current_word_family;
	My_String* pNew_key=(My_String*)new_key;
	My_String* pWord=(My_String*)word;
	//Change the size of the new key to match the key.
	if(pNew_key->capacity<pCurrent_family->size)
	{
		my_string_resize(pNew_key, pCurrent_family->size+1);
	}
	pNew_key->size=pCurrent_family->size;
	//Convert the guess to lowercase.
	//Copy the current word family to the new key, letter by letter.
	for(int i=0;i<pWord->size;i++)
	{
	//>If the current word family has the guess at a point, copy the guess.
	//>If the current word family has a fixed letter, copy it.
	//>Otherwise, leave the space blank.
		if(tolower(pWord->data[i])==tolower(guess))
		{
			pNew_key->data[i]=tolower(guess);
		}
		else if(pCurrent_family->data[i]!='-')
		{
			pNew_key->data[i]=pCurrent_family->data[i];
		}
		else
		{
			pNew_key->data[i]='-';
		}
	}
}

void my_string_destroy(Item* pItem)
{
	My_String* pMy_String=(My_String*)*pItem;
	//printf("Freeing string of length %d\n", pMy_String->size);//Debug code.
	//printf("Attempting to free string data.\n");
	free(pMy_String->data);
	//printf("String data freed.\n");
	free(pMy_String);
	//printf("Memory freed.\n");
	*pItem=NULL;
}

