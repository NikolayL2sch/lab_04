#ifndef STACKIO_H
#define STACKIO_H

#include "structs.h"

int read_stack_type(int *stack_type);
int read_cnt_add_stack_arr(int *num_add, int size);
int read_stack_arr_file(stack_array_t *stack_array, int *num_add, int size, char *filename);
int read_cnt_del_stack_arr(int *num_del, int size);
void print_stack_array(stack_array_t *stack_array);
int read_cnt_add_to_stack_list(int *num_add, elem_stack_list_t *elem_stack_list);
int read_stack_list_file(elem_stack_list_t *elem_stack_list, int *num_add, int size, char *filename);
int read_number_of_remove_elem_from_stack_list(int *num_del, elem_stack_list_t *elem_stack_list);
void print_stack_list(elem_stack_list_t **elem_stack_list);
void print_array(array_of_freed_areas_t *array);

#endif //STACKIO_H