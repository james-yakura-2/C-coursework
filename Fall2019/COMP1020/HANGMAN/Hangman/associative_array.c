#include "associative_array.h"

struct kv_pair
{
	MY_STRING key;
	VECTOR value;
};

typedef struct kv_pair Key_Value_Pair;

typedef struct node Linked_List_Node;

struct node
{
	Key_Value_Pair* value;
	Linked_List_Node* next;
};



struct associative_array
{
	Linked_List_Node** pairs;
	int length;
};

typedef struct associative_array Associative_Array;

//Produces a new Associative Array.
//@param positions The number of "buckets" in the array. For best results, this should be a prime number.
//@returns A new Associative Array.
ASSOCIATIVE_ARRAY associative_array_init_length(int positions)
{
	Associative_Array* arr = NULL;
	arr = (Associative_Array*)malloc(sizeof(Associative_Array));
	if (arr != NULL)
	{
		arr->length = positions;
		arr->pairs = NULL;
		arr->pairs = (Linked_List_Node*)malloc(sizeof(Linked_List_Node) * positions);
		if (arr->pairs == NULL)
		{
			free(arr);
			arr = NULL;
		}
		else
		{
			for (int i = 0; i < positions; i++)
			{
				arr->pairs = NULL;
			}
		}
	}
	return arr;
}

//-use the associative array

//The hash function of the associative array.
//@param hKey A My-String to be hashed.
//@returns An integer used to store the key in the array.
int associative_array_hash(MY_STRING hKey)
{
	int length = my_string_get_size(hKey);
	char* string = my_string_c_str(hKey);
	int hash = 0;
	for (int i = 0; i < length; i++)
	{
		hash *= 128;
		hash += string[i];
	}
	return hash;
}

//Adds a new My-String to the associative array.
//@param hArray The associative array to be used.
//@param hKey The key to be used to store the new My-String in the array.
//@param hValue The string to be stored in the array.
//@returns Success if the item was added successfully, failure otherwise.
Status associative_array_add(ASSOCIATIVE_ARRAY hArray, MY_STRING hKey, MY_STRING hValue)
{
	//Get the vector associated with the key.
	VECTOR vect = associative_array_retrieve(hArray, hKey);
	if (vect == NULL)
	{
		return FAILURE;
	}
	//Add the value to the vector associated with the key.
	return vector_push(vect, my_string_init_c_string(my_string_c_str( hValue)));
}

//Retrieves the vector of My-Strings associated with a key.
//@param hArray The associative array to be used.
//@param hKey The key that the vector was stored under.
//@returns All My-Strings that match the provided key.
VECTOR associative_array_retrieve(ASSOCIATIVE_ARRAY hArray, MY_STRING hKey)
{
	//Look up the "bucket" containing the key.
	Associative_Array* pArray = (Associative_Array*)hArray;
	int index = associative_array_hash(hKey)%pArray->length;
	VECTOR value = NULL;
	Linked_List_Node* attempt = pArray->pairs[index];
	while (attempt != NULL)
	{
		//Compare the strings.
		//If they are not equal, move on; otherwise, the array has been found.
		if (my_string_compare(hKey, attempt->value->key) == 0)
		{
			int length = my_string_get_size(hKey);
			char* key = my_string_c_str(hKey);
			char* compare = my_string_c_str(attempt->value->key);
			
			int match = 1;
			for (int i = 0; i < length; i++)
			{
				if (key[i] != compare[i])
				{
					match = 0;
					break;
				}
			}
			if (match > 0)
			{
				value = attempt->value->value;
				break;
			}
			
		}
		if (value != NULL)
		{
			break;
		}
		attempt = attempt->next;
	}

	//If the key is not assigned, return an empty vector and add it to the "bucket".
	if (value == NULL)
	{
		Linked_List_Node* new_node = NULL;
		new_node = (Linked_List_Node*)malloc(sizeof(Linked_List_Node));
		if (new_node != NULL)
		{
			new_node->next = pArray->pairs[index];
			Key_Value_Pair* kvp = NULL;
			kvp = (Key_Value_Pair*)malloc(sizeof(Key_Value_Pair));
			if (kvp != NULL)
			{
				kvp->key = my_string_init_c_string(my_string_c_str(hKey));
				value = vector_init_default();
				if (value == NULL)
				{
					free(kvp);
					free(new_node);
				}
				else
				{
					pArray->pairs[index] = new_node;
				}
			}
			else
			{
				free(new_node);
			}
		}

	}

	//Otherwise, return the associated vector.

	return value;
}

//Gets the list of all keys in the associative array.
//@param hArray The associative array to be used.
//@returns A vector of all keys that have been stored in the array.
VECTOR associative_array_get_keys(ASSOCIATIVE_ARRAY hArray)
{
	//For each bucket, add each of its assigned keys to the array.
	VECTOR value = vector_init_default();
	Associative_Array* pArray = (Associative_Array*)hArray;
	for (int i = 0; i < pArray->length; i++)
	{
		Linked_List_Node* trying = pArray->pairs[i];
		while (trying != NULL)
		{
			vector_push(value, trying->value->key);
			trying = trying->next;
		}
	}
	return value;
}


//-destroy the associative array
//Destroys an associative array, freeing all memory associated with it.
//@param hAssoc The associative array to be destroyed.
void associative_array_destroy(ASSOCIATIVE_ARRAY* hAssoc)
{
	Associative_Array* pAssoc = (Associative_Array*)hAssoc;
	//For each bucket, go through its contents and free each vector and its key, then the node holding them.
	for (int i = 0; i < pAssoc->length; i++)
	{
		Linked_List_Node* deleting = pAssoc->pairs[i];
		while (deleting != NULL)
		{
			vector_destroy(deleting->value->value);
			my_string_destroy(deleting->value->key);
			Linked_List_Node* next = deleting->next;
			free(deleting->value);
			free(deleting);
			deleting = next;
		}
	}
	//Then, free the buckets.
	free(pAssoc->pairs);
	//Then, free the array.
	free(pAssoc);
	hAssoc = NULL;
}