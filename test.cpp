#include <stdio.h>
#include <malloc.h>
#include "include/stack.h"
#include "include/print.h"
#include "include/test.h"

unsigned int test_stack_1(const ssize_t stack_size)
{
	struct Stack stk;

	get_stack_call_info(); 

	enum error_code init_code =  stack_init(&stk, stack_size);

	if (init_code != NO_ERROR)
	{
		print_error(init_code);
		return init_code;
	}

	printf("test stack 1 has been init\n");

	unsigned int error_code = stack_verificator(&stk);

	print_error(error_code);

	print_stack(&stk, stack_size);

	for (ssize_t push_number = 0; push_number < stack_size + 1; push_number++)
	{
		stack_push(&stk, push_number);
		print_data(&stk, stack_size);
	}

	elem_t pop_value = POISON_VALUE;

	for (ssize_t pop_number = stack_size - 1; pop_number >= 0; pop_number--)
	{
		stack_pop(&stk, &pop_value);
		print_data(&stk, stack_size);
		printf("popped number is %d\n", pop_value); // %d только для int 
	}

	stack_dtor(&stk);

	printf("test stack 1 has been destroyed\n");

	return NO_ERROR;
}


