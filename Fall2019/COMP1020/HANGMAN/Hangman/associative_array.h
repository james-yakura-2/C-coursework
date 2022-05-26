#pragma once
#include "my_string.h"
#include "vector.h"

//An array associating vectors of MY_STRING objects with keys describing them.
typedef void* ASSOCIATIVE_ARRAY;
//-create the associative array

//Produces a new Associative Array.
//@param positions The number of "buckets" in the array. For best results, this should be a prime number.
//@returns A new Associative Array.
ASSOCIATIVE_ARRAY associative_array_init_length(int positions);

//-use the associative array

//The hash function of the associative array.
//@param hKey A My-String to be hashed.
//@returns An integer used to store the key in the array.
int associative_array_hash(MY_STRING hKey);

//Adds a new My-String to the associative array.
//@param hArray The associative array to be used.
//@param hKey The key to be used to store the new My-String in the array.
//@param hValue The string to be stored in the array.
//@returns Success if the item was added successfully, failure otherwise.
Status associative_array_add(ASSOCIATIVE_ARRAY hArray, MY_STRING hKey, MY_STRING hValue);

//Retrieves the vector of My-Strings associated with a key.
//@param hArray The associative array to be used.
//@param hKey The key that the vector was stored under.
//@returns All My-Strings that match the provided key.
VECTOR associative_array_retrieve(ASSOCIATIVE_ARRAY hArray, MY_STRING hKey);

//Gets the list of all keys in the associative array.
//@param hArray The associative array to be used.
//@returns A vector of all keys that have been stored in the array.
VECTOR associative_array_get_keys(ASSOCIATIVE_ARRAY hArray);


//-destroy the associative array
//Destroys an associative array, freeing all memory associated with it.
//@param hAssoc The associative array to be destroyed.
void associative_array_destroy(ASSOCIATIVE_ARRAY* hAssoc);