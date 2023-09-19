#ifndef PRINT_H
#define PRINT_H

#include "stack.h"

unsigned int print_stack(const struct Stack* const stk_ptr, ssize_t print_data_count);

unsigned int print_error(unsigned int error_code);

unsigned int print_data(const Stack*  const stk_ptr, ssize_t print_poison_data_count);

#endif /* PRINT_H */