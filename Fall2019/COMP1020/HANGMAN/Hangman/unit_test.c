#include <stdio.h>
#include "unit_test.h"
#include "my_string.h"

int main(int argc, char* argv[])
{
   Status (*tests[])(char*, int) =
       {
	test_init_default_returns_nonNULL,
	test_get_size_on_init_default_returns_0,
	test_init_c_string_returns_nonNULL,
	test_get_size_after_init_hello_returns_5,
	test_get_capacity_after_init_hello_returns_6,

	test_compare_hello_world_returns_0,
	test_compare_hellos_world_returns_positive,
	test_compare_hello_worlds_returns_negative,
	test_get_size_after_push_s_to_hello_returns_6,
	test_get_capacity_after_push_ss_to_hello_returns_12,

	test_get_size_after_pop_from_hello_returns_4,
	test_get_capacity_after_pop_from_hello_returns_6,
	test_at_0_of_hello_returns_h,
	test_at_1_of_hello_returns_e,
	test_at_2_of_hello_returns_l,

	test_at_3_of_hello_returns_l,
	test_at_4_of_hello_returns_o,
	test_at_5_of_hello_returns_NULL,
	test_at_negative_of_hello_returns_NULL,
	test_at_5_of_hello_after_push_s_returns_s,

	test_at_6_of_hello_after_push_s_returns_NULL,
	test_c_string_0_of_hello_returns_h,
	test_init_c_string_of_c_string_of_hello_returns_nonNULL,
	test_at_0_after_init_c_string_of_c_string_of_hello_returns_h,
	test_get_size_after_concat_hello_world_returns_10
       };
   int number_of_functions = sizeof(tests) / sizeof(tests[0]);
   int i;
   char buffer[500];
   int success_count = 0;
   int failure_count = 0;
   for(i=0; i<number_of_functions; i++)
   {
      if(tests[i](buffer, 500) == FAILURE)
      {
         printf("FAILED: Test %d failed miserably\n", i);
         printf("\t%s\n", buffer);
         failure_count++;
      }
      else
      {
	// printf("PASS: Test %d passed\n", i);
	// printf("\t%s\n", buffer);
	success_count++;
      }
   }
   printf("Total number of tests: %d\n", number_of_functions);
   printf("%d/%d Pass, %d/%d Failure\n", success_count, number_of_functions, failure_count, number_of_functions);
   return 0;
}
