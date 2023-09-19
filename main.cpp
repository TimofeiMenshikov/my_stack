#include <stdio.h>
#include <malloc.h>
#include "include/stack.h"
#include "include/print.h"

const ssize_t stack_size = 10;

int main()
{
	struct Stack stk;

	stk.stk_info.call_line = __LINE__;
	stk.stk_info.call_func = __func__;
	stk.stk_info.call_file = __FILE__;

	stack_init(&stk, stack_size);

	printf("stack has been init\n");

	unsigned int error_code = stack_verificator(&stk);

	print_error(error_code);

	stk.size = 3;

	print_stack(&stk, 10);

	stack_dtor(&stk);

	print_stack(&stk, 10);
}