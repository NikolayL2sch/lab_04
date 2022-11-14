#ifndef STACK_LIST_FUNCS_H
#define STACK_LIST_FUNCS_H

#include "structs.h"

int work_with_stack_list(void);
int add_elem_to_stack_list(elem_stack_list_t **elem_stack_list, int num_add, array_of_freed_areas_t *array);
void free_stack_list(elem_stack_list_t **elem_stack_list);
int add_addresses_of_removed_elem_to_array(array_of_freed_areas_t *array, int num_del, elem_stack_list_t *elem_stack_list);
void remove_elem_from_stack_list(elem_stack_list_t **elem_stack_list, int num_del);
void print_descend_sequen_stack_list(elem_stack_list_t *elem_stack_list, FILE *f);
int fill_stack_list_randomly(elem_stack_list_t **elem_stack_list, int numb_add_elem);

#endif
