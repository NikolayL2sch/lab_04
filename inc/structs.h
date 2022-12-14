#ifndef STRUCTURES_H
#define STRUCTURES_H

#include "constants.h"

typedef struct stack_array
{
    int *ptr;
    int size;
} stack_array_t;

typedef struct elem_stack_list
{
    int elem;
    int num_elem;
    struct elem_stack_list *next;
} elem_stack_list_t;

typedef struct array_of_freed_areas
{
    elem_stack_list_t **array;
    int size;
} array_of_freed_areas_t;

#endif