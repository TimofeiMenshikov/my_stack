#include <stdio.h>
#include <malloc.h>
#include "include/stack.h"
#include "include/print.h"
#include "include/test.h"

const ssize_t stack_size = 10;


int main()
{
	struct Stack stk;

	get_stack_call_info(); 

	stack_init(&stk, stack_size);

	printf("stack has been init\n");

	unsigned int error_code = stack_verificator(&stk);

	print_error(error_code);

	print_stack(&stk, stack_size);

	for (ssize_t push_number = 0; push_number < stack_size + 1; push_number++)
	{
		stack_push(&stk, push_number);
		print_data(&stk, stack_size);
	}

	stack_dtor(&stk);
}