#ifndef UNIT_TEST_H
#define UNIT_TEST_H
#include "my_string.h"
Status test_init_default_returns_nonNULL(char* buffer, int length);
Status test_get_size_on_init_default_returns_0(char* buffer, int length);
Status test_init_c_string_returns_nonNULL(char* buffer, int length);
Status test_get_size_after_init_hello_returns_5(char* buffer, int length);
Status test_get_capacity_after_init_hello_returns_6(char* buffer, int length);

Status test_compare_hello_world_returns_0(char* buffer, int length);
Status test_compare_hellos_world_returns_positive(char* buffer, int length);
Status test_compare_hello_worlds_returns_negative(char* buffer, int length);
Status test_get_size_after_push_s_to_hello_returns_6(char* buffer, int length);
Status test_get_capacity_after_push_ss_to_hello_returns_12(char* buffer, int length);

Status test_get_size_after_pop_from_hello_returns_4(char*buffer, int length);
Status test_get_capacity_after_pop_from_hello_returns_6(char* buffer, int length);
Status test_at_0_of_hello_returns_h(char* buffer, int length);
Status test_at_1_of_hello_returns_e(char* buffer, int length);
Status test_at_2_of_hello_returns_l(char* buffer, int length);

Status test_at_3_of_hello_returns_l(char* buffer, int length);
Status test_at_4_of_hello_returns_o(char* buffer, int length);
Status test_at_5_of_hello_returns_NULL(char* buffer, int length);
Status test_at_negative_of_hello_returns_NULL(char* buffer, int length);
Status test_at_5_of_hello_after_push_s_returns_s(char* buffer, int length);

Status test_at_6_of_hello_after_push_s_returns_NULL(char* buffer, int length);
Status test_c_string_0_of_hello_returns_h(char* buffer, int length);
Status test_init_c_string_of_c_string_of_hello_returns_nonNULL(char* buffer, int length);
Status test_at_0_after_init_c_string_of_c_string_of_hello_returns_h(char* buffer, int length);
Status test_get_size_after_concat_hello_world_returns_10(char* buffer, int length);
#endif
