#include "my_string.h"
#include <string.h>
//1
Status test_init_default_returns_nonNULL(char* buffer, int length)
{
   MY_STRING hString = NULL;
   hString = my_string_init_default();
   if(hString == NULL)
   {
      my_string_destroy((Item*)&hString);
      strncpy(buffer, "test_init_default_returns_nonNULL\n" "my_string_init_default returns NULL", length);
      return FAILURE;
   }
   else
   {
      my_string_destroy((Item*)&hString);
      strncpy(buffer, "\ttest_init_default_returns_nonNULL\n", length);
      return SUCCESS;
   }
} 
//2
Status test_get_size_on_init_default_returns_0(char* buffer, int length)
{
   MY_STRING hString = NULL;
   Status status;
   hString = my_string_init_default();
   if(my_string_get_size(hString) != 0)
   {
      status = FAILURE;
      printf("Expected a size of 0 but got %d\n", my_string_get_size(hString));
      strncpy(buffer, "test_get_size_on_init_default_returns_0\n" "Did not receive 0 from get_size after init_default\n", length);
   }
   else
   {
      status = SUCCESS;
      strncpy(buffer, "test_get_size_on_init_default_returns_0\n", length);
   }
   my_string_destroy((Item*)&hString);
   return status;
}
//3
Status test_init_c_string_returns_nonNULL(char* buffer, int length)
{
   MY_STRING hString = NULL;
   hString = my_string_init_c_string("Hello");
   if(hString == NULL)
   {
      my_string_destroy((Item*)&hString);
      strncpy(buffer, "test_init_c_string_returns_nonNULL\n" "my_string_init_c_string returns NULL", length);
      return FAILURE;
   }
   else
   {
      my_string_destroy((Item*)&hString);
      strncpy(buffer, "\tttest_init_c_string_returns_nonNULL\n", length);
      return SUCCESS;
   }
} 
//4
Status test_get_size_after_init_hello_returns_5(char* buffer, int length)
{
   MY_STRING hString = NULL;
   Status status;
   hString = my_string_init_c_string("Hello");
   
   if(my_string_get_size(hString) != 5)
   {
      status = FAILURE;
      printf("Expected a size of 5 but got %d\n", my_string_get_size(hString));
      strncpy(buffer, "test_get_size_after_init_hello_returns_5\n" "Did not receive 5 from get_size after init_default\n", length);
   }
   else
   {
      status = SUCCESS;
      strncpy(buffer, "test_get_size_after_init_hello_returns_5\n", length);
   }
   my_string_destroy((Item*)&hString);
   return status;
}
//5
Status test_get_capacity_after_init_hello_returns_6(char* buffer, int length)
{
   MY_STRING hString = NULL;
   Status status;
   hString = my_string_init_c_string("Hello");
   
   if(my_string_get_capacity(hString) != 6)
   {
      status = FAILURE;
      printf("Expected a capacity of 6 but got %d\n", my_string_get_capacity(hString));
      strncpy(buffer, "test_get_capacity_after_init_hello_returns_6\n" "Did not receive 6 from get_capacity after init_default\n", length);
   }
   else
   {
      status = SUCCESS;
      strncpy(buffer, "test_get_capacity_after_init_hello_returns_6\n", length);
   }
   my_string_destroy((Item*)&hString);
   return status;
}
//6
Status test_compare_hello_world_returns_0(char* buffer, int length)
{
   MY_STRING hString = NULL;
   Status status;
   hString = my_string_init_c_string("Hello");
      MY_STRING hString2=NULL;
   hString2 = my_string_init_c_string("World");
   
   if(my_string_compare(hString, hString2) != 0)
   {
      status = FAILURE;
      printf("Expected a compare of 0 but got %d\n", my_string_compare(hString, hString2));
      strncpy(buffer, "test_compare_hello_world_returns_0\n" "Did not receive 0 from compare\n", length);
   }
   else
   {
      status = SUCCESS;
      strncpy(buffer, "test_compare_hello_world_returns_0\n", length);
   }
   my_string_destroy((Item*)&hString);
   my_string_destroy((Item*)&hString2);
   return status;
}

Status test_compare_hellos_world_returns_positive(char* buffer, int length)
{
   MY_STRING hString = NULL;
   Status status;
   hString = my_string_init_c_string("Hellos");
   MY_STRING hString2=NULL;
   hString2 = my_string_init_c_string("World");
   
   if(my_string_compare(hString, hString2) < 0)
   {
      status = FAILURE;
      printf("Expected a compare of positive but got %d\n", my_string_compare(hString, hString2));
      strncpy(buffer, "test_compare_hellos_world_returns_positive\n" "Did not receive positive from compare\n", length);
   }
   else
   {
      status = SUCCESS;
      strncpy(buffer, "test_compare_hellos_world_returns_positive\n", length);
   }
   my_string_destroy((Item*)&hString);
   my_string_destroy((Item*)&hString2);
   return status;
}

Status test_compare_hello_worlds_returns_negative(char* buffer, int length)
{
   MY_STRING hString = NULL;
   Status status;
   hString = my_string_init_c_string("Hello");
   MY_STRING hString2=NULL;
   hString2 = my_string_init_c_string("Worlds");
   
   if(my_string_compare(hString, hString2) > 0)
   {
      status = FAILURE;
      printf("Expected a compare of negative but got %d\n", my_string_compare(hString, hString2));
      strncpy(buffer, "test_compare_hello_worlds_returns_negative\n" "Did not receive negative from compare\n", length);
   }
   else
   {
      status = SUCCESS;
      strncpy(buffer, "test_compare_hello_worlds_returns_negative\n", length);
   }
   my_string_destroy((Item*)&hString);
   my_string_destroy((Item*)&hString2);
   return status;
}

Status test_get_size_after_push_s_to_hello_returns_6(char* buffer, int length)
{
   MY_STRING hString = NULL;
   Status status;
   hString = my_string_init_c_string("Hello");
   my_string_push_back(hString, 's');
   
   if(my_string_get_size(hString) != 6)
   {
      status = FAILURE;
      printf("Expected a size of 6 but got %d\n", my_string_get_size(hString));
      strncpy(buffer, "test_get_size_after_push_s_to_hello_returns_6\n" "Did not receive 6 from get_size after push_back\n", length);
   }
   else
   {
      status = SUCCESS;
      strncpy(buffer, "test_get_size_after_push_s_to_hello_returns_6\n", length);
   }
   my_string_destroy((Item*)&hString);
   return status;
}

Status test_get_capacity_after_push_ss_to_hello_returns_12(char* buffer, int length)
{
   MY_STRING hString = NULL;
   Status status;
   hString = my_string_init_c_string("Hello");
   my_string_push_back(hString, 's');
   my_string_push_back(hString, 's');
   
   if(my_string_get_capacity(hString) != 12)
   {
      status = FAILURE;
      printf("Expected a capacity of 12 but got %d\n", my_string_get_capacity(hString));
      strncpy(buffer, "test_get_capacity_after_push_ss_to_hello_returns_12\n" "Did not receive 12 from get_capacity after push_back\n", length);
   }
   else
   {
      status = SUCCESS;
      strncpy(buffer, "test_get_capacity_after_push_s_to_hello_returns_10\n", length);
   }
   my_string_destroy((Item*)&hString);
   return status;
}

Status test_get_size_after_pop_from_hello_returns_4(char*buffer, int length)
{
   MY_STRING hString = NULL;
   Status status;
   hString = my_string_init_c_string("Hello");
   my_string_pop_back(hString);
   
   if(my_string_get_size(hString) != 4)
   {
      status = FAILURE;
      printf("Expected a size of 4 but got %d\n", my_string_get_size(hString));
      strncpy(buffer, "test_get_size_after_pop_from_hello_returns_4\n" "Did not receive 4 from get_size after pop_back\n", length);
   }
   else
   {
      status = SUCCESS;
      strncpy(buffer, "test_get_size_after_pop_from_hello_returns_4\n", length);
   }
   my_string_destroy((Item*)&hString);
   return status;
}

Status test_get_capacity_after_pop_from_hello_returns_6(char* buffer, int length)
{
   MY_STRING hString = NULL;
   Status status;
   hString = my_string_init_c_string("Hello");
   my_string_pop_back(hString);
   
   if(my_string_get_capacity(hString) != 6)
   {
      status = FAILURE;
      printf("Expected a capacity of 6 but got %d\n", my_string_get_capacity(hString));
      strncpy(buffer, "test_get_capacity_after_pop_from_hello_returns_5\n" "Did not receive 6 from get_capacity after pop_back\n", length);
   }
   else
   {
      status = SUCCESS;
      strncpy(buffer, "test_get_capacity_after_pop_from_hello_returns_5\n", length);
   }
   my_string_destroy((Item*)&hString);
   return status;
}

Status test_at_0_of_hello_returns_h(char* buffer, int length)
{
   MY_STRING hString = NULL;
   Status status;
   hString = my_string_init_c_string("Hello");
   
   if(my_string_at(hString,0)[0] != 'H')
   {
      status = FAILURE;
      printf("Expected a value of H but got %c\n", my_string_at(hString,0)[0]);
      strncpy(buffer, "test_at_0_of_hello_returns_h\n" "Did not receive H from at after init_c_string\n", length);
   }
   else
   {
      status = SUCCESS;
      strncpy(buffer, "test_at_0_of_hello_returns_h\n", length);
   }
   my_string_destroy((Item*)&hString);
   return status;
}

Status test_at_1_of_hello_returns_e(char* buffer, int length)
{
   MY_STRING hString = NULL;
   Status status;
   hString = my_string_init_c_string("Hello");
   
   if(my_string_at(hString,1)[0] != 'e')
   {
      status = FAILURE;
      printf("Expected a value of e but got %c\n", my_string_at(hString,1)[0]);
      strncpy(buffer, "test_at_1_of_hello_returns_e\n" "Did not receive e from at after init_c_string\n", length);
   }
   else
   {
      status = SUCCESS;
      strncpy(buffer, "test_at_1_of_hello_returns_e\n", length);
   }
   my_string_destroy((Item*)&hString);
   return status;
}

Status test_at_2_of_hello_returns_l(char* buffer, int length)
{
   MY_STRING hString = NULL;
   Status status;
   hString = my_string_init_c_string("Hello");
   
   if(my_string_at(hString,2)[0] != 'l')
   {
      status = FAILURE;
      printf("Expected a value of l but got %c\n", my_string_at(hString,2)[0]);
      strncpy(buffer, "test_at_2_of_hello_returns_l\n" "Did not receive l from at after init_c_string\n", length);
   }
   else
   {
      status = SUCCESS;
      strncpy(buffer, "test_at_2_of_hello_returns_l\n", length);
   }
   my_string_destroy((Item*)&hString);
   return status;
}

Status test_at_3_of_hello_returns_l(char* buffer, int length)
{
   MY_STRING hString = NULL;
   Status status;
   hString = my_string_init_c_string("Hello");
   
   if(my_string_at(hString,3)[0] != 'l')
   {
      status = FAILURE;
      printf("Expected a value of l but got %c\n", my_string_at(hString,3)[0]);
      strncpy(buffer, "test_at_3_of_hello_returns_l\n" "Did not receive l from at after init_c_string\n", length);
   }
   else
   {
      status = SUCCESS;
      strncpy(buffer, "test_at_3_of_hello_returns_l\n", length);
   }
   my_string_destroy((Item*)&hString);
   return status;
}

Status test_at_4_of_hello_returns_o(char* buffer, int length)
{
   MY_STRING hString = NULL;
   Status status;
   hString = my_string_init_c_string("Hello");
   
   if(my_string_at(hString,4)[0] != 'o')
   {
      status = FAILURE;
      printf("Expected a value of o but got %c\n", my_string_at(hString,4)[0]);
      strncpy(buffer, "test_at_4_of_hello_returns_o\n" "Did not receive o from at after init_c_string\n", length);
   }
   else
   {
      status = SUCCESS;
      strncpy(buffer, "test_at_4_of_hello_returns_o\n", length);
   }
   my_string_destroy((Item*)&hString);
   return status;
}

Status test_at_5_of_hello_returns_NULL(char* buffer, int length)
{
   MY_STRING hString = NULL;
   Status status;
   hString = my_string_init_c_string("Hello");
   
   if(my_string_at(hString,5) != NULL)
   {
      status = FAILURE;
      printf("Expected a value of NULL but got %s\n", my_string_at(hString,5));
      strncpy(buffer, "test_at_5_of_hello_returns_NULL\n" "Did not receive NULL from at after init_c_string\n", length);
   }
   else
   {
      status = SUCCESS;
      strncpy(buffer, "test_at_5_of_hello_returns_NULL\n", length);
   }
   my_string_destroy((Item*)&hString);
   return status;
}

Status test_at_negative_of_hello_returns_NULL(char* buffer, int length)
{
   MY_STRING hString = NULL;
   Status status;
   hString = my_string_init_c_string("Hello");
   
   if(my_string_at(hString,-1) != NULL)
   {
      status = FAILURE;
      printf("Expected a value of NULL but got %s\n", my_string_at(hString,-1));
      strncpy(buffer, "test_at_negative_of_hello_returns_NULL\n" "Did not receive NULL from at after init_c_string\n", length);
   }
   else
   {
      status = SUCCESS;
      strncpy(buffer, "test_at_negative_of_hello_returns_NULL\n", length);
   }
   my_string_destroy((Item*)&hString);
   return status;
}

Status test_at_5_of_hello_after_push_s_returns_s(char* buffer, int length)
{
   MY_STRING hString = NULL;
   Status status;
   hString = my_string_init_c_string("Hello");
   my_string_push_back(hString, 's');
   
   if(my_string_at(hString,5)[0] != 's')
   {
      status = FAILURE;
      printf("Expected a value of s but got %c\n", my_string_at(hString,5)[0]);
      strncpy(buffer, "test_at_5_of_hello_after_push_s_returns_s\n" "Did not receive s from at after push_back\n", length);
   }
   else
   {
      status = SUCCESS;
      strncpy(buffer, "test_at_5_of_hello_after_push_s_returns_s\n", length);
   }
   my_string_destroy((Item*)&hString);
   return status;
}

Status test_at_6_of_hello_after_push_s_returns_NULL(char* buffer, int length)
{
   MY_STRING hString = NULL;
   Status status;
   hString = my_string_init_c_string("Hello");
   my_string_push_back(hString, 's');
   
   if(my_string_at(hString,6) != NULL)
   {
      status = FAILURE;
      printf("Expected a value of NULL but got %s\n", my_string_at(hString,6));
      strncpy(buffer, "test_at_6_of_hello_after_push_s_returns_NULL\n" "Did not receive NULL from at after push_back\n", length);
   }
   else
   {
      status = SUCCESS;
      strncpy(buffer, "test_at_6_of_hello_after_push_s_returns_NULL\n", length);
   }
   my_string_destroy((Item*)&hString);
   return status;
}

Status test_c_string_0_of_hello_returns_h(char* buffer, int length)
{
   MY_STRING hString = NULL;
   Status status;
   hString = my_string_init_c_string("Hello");
   
   if(my_string_c_str(hString)[0] != 'H')
   {
      status = FAILURE;
      printf("Expected a value of H but got %c\n", my_string_c_str(hString)[0]);
      strncpy(buffer, "test_c_string_of_hello_returns_hello\n" "Did not receive Hello from at after init_c_string\n", length);
   }
   else
   {
      status = SUCCESS;
      strncpy(buffer, "test_c_string_of_hello_returns_hello\n", length);
   }
   my_string_destroy((Item*)&hString);
   return status;
}

Status test_init_c_string_of_c_string_of_hello_returns_nonNULL(char* buffer, int length)
{
   MY_STRING hString = NULL;
   Status status;
   hString = my_string_init_c_string("Hello");
   MY_STRING hString2=NULL;
   hString2= my_string_init_c_string(my_string_c_str(hString));
   
   if(hString2 == NULL)
   {
      status = FAILURE;
      strncpy(buffer, "test_init_c_string_of_c_string_of_hello_returns_nonNULL\n" "my_string_init_c_string returns NULL\n", length);
   }
   else
   {
      status = SUCCESS;
      strncpy(buffer, "test_init_c_string_of_c_string_of_hello_returns_nonNULL\n", length);
   }
   my_string_destroy((Item*)&hString);
   my_string_destroy((Item*)&hString2);
   return status;
}

Status test_at_0_after_init_c_string_of_c_string_of_hello_returns_h(char* buffer, int length)
{
   MY_STRING hString = NULL;
   Status status;
   hString = my_string_init_c_string("Hello");

   MY_STRING hString2=NULL;
   hString2= my_string_init_c_string(my_string_c_str(hString));
   
   if(my_string_at(hString2,0)[0] != 'H')
   {
      status = FAILURE;
      printf("Expected a value of H but got %c\n", my_string_at(hString2,0)[0]);
      strncpy(buffer, "test_at_0_after_init_c_string_of_c_string_of_hello_returns_h\n" "Did not receive H from at after init_c_string\n", length);
   }
   else
   {
      status = SUCCESS;
      strncpy(buffer, "test_at_0_after_init_c_string_of_c_string_of_hello_returns_h\n", length);
   }
   my_string_destroy((Item*)&hString);
   my_string_destroy((Item*)&hString2);
   return status;
}

Status test_get_size_after_concat_hello_world_returns_10(char* buffer, int length)
{
   MY_STRING hString = NULL;
   Status status;
   hString = my_string_init_c_string("Hello");
   MY_STRING hString2=NULL;
   hString2= my_string_init_c_string("World");
   my_string_concat(hString, hString2);
   
   if(my_string_get_size(hString) != 10)
   {
      status = FAILURE;
      printf("Expected a size of 10 but got %d\n", my_string_get_size(hString2));
      strncpy(buffer, "test_get_size_after_concat_hello_world_returns_10\n" "Did not receive 10 from get_size after concat\n", length);
   }
   else
   {
      status = SUCCESS;
      strncpy(buffer, "test_get_size_after_concat_hello_world_returns_10\n", length);
   }
   my_string_destroy((Item*)&hString);
   my_string_destroy((Item*)&hString2);
   return status;
}


