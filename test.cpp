#include <stdio.h>
#include <malloc.h>
#include "include/stack.h"
#include "include/print.h"
#include "include/test.h"


#define start_test()         								   \
	struct Stack stk;       								   \
															   \
	get_stack_call_info();  								   \
															   \
	enum error_code init_code =  stack_init(&stk, stack_size); \
															   \
	if (init_code != NO_ERROR)								   \
	{														   \
		print_error(init_code);								   \
		return init_code;									   \
	}														   \
															   \
															   \
	unsigned int error_code = stack_verificator(&stk);         \
															   \
	print_error(error_code);								   \
															   \
	print_stack(&stk, stack_size);  						   



unsigned int test_stack_1(const ssize_t stack_size)
{
	start_test();

	for (ssize_t push_number = 0; push_number < stack_size * 5; push_number++)
	{
		stack_push(&stk, push_number);
		print_stack(&stk, stk.capacity);
	}

	elem_t pop_value = POISON_VALUE;

	for (ssize_t pop_number = stack_size - 1; pop_number >= 0; pop_number--)
	{
		stack_pop(&stk, &pop_value);
		print_stack(&stk, stk.capacity);
		printf("popped number is %d\n", pop_value); // %d только для int 
	}

	stack_dtor(&stk);

	printf("test stack 1 has been destroyed\n");

	return NO_ERROR;
}


unsigned int test_print_data(const ssize_t stack_size)
{
	start_test();

	stk.size = 3;

	for (ssize_t print_poison_data_count = 0; print_poison_data_count < stk.capacity; print_poison_data_count++)
	{
		print_data(&stk, print_poison_data_count);
	}

	return NO_ERROR;
}


unsigned int test_increase_stack(const ssize_t stack_size, const size_t increase_coef)
{
	start_test();

	increase_stack(increase_coef, &stk);

	print_stack(&stk, stk.capacity);



	return NO_ERROR;
}


unsigned int test_decrease_stack(const ssize_t stack_size, const size_t decrease_coef)
{
	start_test();

	stk.size = 5;

	decrease_stack(decrease_coef, &stk);

	print_stack(&stk, stk.capacity);


	return NO_ERROR;
} 