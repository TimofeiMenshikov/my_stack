#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "include/stack.h"
#include "include/print.h"
#include "include/canary.h"
#include "include/hash.h"


#define start_test()         								   \
	struct Stack stk;       								   \
															   \
	get_stack_call_info();  								   \
															   \
	enum error_code init_code =  stack_init(&stk, stack_size); \
															   \
	if (init_code != NO_ERROR)								   \
	{														   \
		print_stack_error(init_code);						   \
		return init_code;									   \
	}														   \
															   \
															   \
	unsigned int error_code = stack_verificator(&stk);         \
															   \
	print_stack_error(error_code);							   \
															   \
	print_stack(&stk, stack_size);  						   



static unsigned int test_stack(const ssize_t stack_size)
{
	start_test();

	for (ssize_t push_number = 0; push_number < stack_size; push_number++)
	{
		stack_push(&stk, push_number);
		print_stack(&stk, stk.capacity);
	}

	for (ssize_t pop_number = stack_size - 1; pop_number >= 0; pop_number--)
	{
		stack_pop(&stk);
		print_stack(&stk, stk.capacity);
		STDOUT_PRINT(printf("popped number is %d\n", stk.last_popped_value)); // %d только для int 
	}

	stack_dtor(&stk);

	STDOUT_PRINT(printf("test stack 1 has been destroyed\n"));

	return NO_ERROR;
}


static unsigned int test_print_data(const ssize_t stack_size)
{
	start_test();

	stk.size = 3;

	for (ssize_t print_poison_data_count = 0; print_poison_data_count < stk.capacity; print_poison_data_count++)
	{
		print_data(&stk, print_poison_data_count);
	}

	stack_dtor(&stk);

	return NO_ERROR;
}


static unsigned int test_increase_stack(const ssize_t stack_size)
{
	start_test();

	increase_stack(&stk);

	print_stack(&stk, stk.capacity);

	stack_dtor(&stk);

	return NO_ERROR;
}


static unsigned int test_decrease_stack(const ssize_t stack_size)
{
	start_test();

	stk.size = 5;

	decrease_stack(&stk);

	print_stack(&stk, stk.capacity);

	stack_dtor(&stk);

	return NO_ERROR;
} 


static unsigned int test_alloc_data()
{
	ssize_t capacity = 5;

	elem_t* data = init_stack_data(capacity);


	#ifdef CANARY_PROTECTION

		STDOUT_PRINT(printf("left canary: %llu\n", *(get_left_canary_ptr(data))));

		STDOUT_PRINT(printf("right canary: %llu\n", *(get_right_canary_ptr(data, capacity))));	

	#endif /* CANARY_PROTECTION */

	for (ssize_t n_elem = 0; n_elem < capacity; n_elem++)
	{
		STDOUT_PRINT(printf("element %zu [%p]: %d\n", n_elem, data + n_elem, data[n_elem]));
	}

	free_data(data);

	STDOUT_PRINT(printf("data is free\n"));

	return NO_ERROR;
}


static unsigned int test_print_stack_error()
{
	print_stack_error((1 << 13) - 1);

	return NO_ERROR;
}


static unsigned int test_calc_hash_sum()
{
	const char* str = "abc";

	size_t mem_str_size = sizeof(char) * 3;

	hash_t test_hash = calc_hash_sum(str, mem_str_size);


	printf(HASH_PRINTF_SPEC, test_hash);

	return NO_ERROR;
}


int main(int argc, char* argv[])
{
	for (size_t test_number = 1; test_number < argc; test_number++)
	{
		if       (strcmp(argv[test_number], "test_stack_1")          == 0)
		{
			test_stack(10);
		}
		else if (strcmp(argv[test_number], "test_stack_2") 		     == 0)
		{
			test_stack(0);
		}
		else if (strcmp(argv[test_number], "test_stack_3") 		     == 0)
		{
			test_stack(-1);
		}
		else if (strcmp(argv[test_number], "test_increase_stack")    == 0)
		{
			test_increase_stack(5);
		}
		else if (strcmp(argv[test_number], "test_decrease_stack")    == 0)
		{
			test_decrease_stack(7);
		}
		else if (strcmp(argv[test_number], "test_print_data") 	     == 0)
		{
			test_print_data(10);
		}
		else if (strcmp(argv[test_number], "test_print_stack_error") == 0)
		{
			test_print_stack_error();
		}
		else if (strcmp(argv[test_number], "test_alloc_data")        == 0)
		{
			test_alloc_data();
		}
		else if (strcmp(argv[test_number], "test_calc_hash_sum")     == 0)
		{
			test_calc_hash_sum();
		}
	}
}
