#ifndef STACK_ARR_FUNCS_H
#define STACK_ARR_FUNCS_H

#include "structs.h"

int work_with_stack_array(void);
int add_elem_to_stack_array(stack_array_t *stack_array, int num_add);
void remove_elem_from_stack_array(stack_array_t *stack_array, int num_del);
void print_descend_sequen_stack_array(stack_array_t stack_array, FILE *f);
void fill_stack_array_randomly(stack_array_t *stack_array, int numb_add_elem);

#endif //STACK_ARR_FUNCS_H