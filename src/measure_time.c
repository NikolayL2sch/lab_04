#include "constants.h"
#include "structs.h"
#include "menu.h"
#include "errors.h"
#include "stackio.h"
#include "stack_arr_funcs.h"
#include "stack_list_funcs.h"

uint64_t tick(void)
{
    uint32_t high, low;
    __asm__ __volatile__ (
        "rdtsc\n"
        "movl %%edx, %0\n"
        "movl %%eax, %1\n"
        : "=r" (high), "=r" (low)
        :: "%rax", "%rbx", "%rcx", "%rdx"
        );

    uint64_t ticks = ((uint64_t)high << 32) | low;

    return ticks;
}

void print_time(int64_t start, int64_t end)
{
    printf("%d tacts, %.10lf seconds\n", (int)(end - start), (double)(end - start)/GHZ);  
}

int compare_stacks(void)
{
    int choice, rc, num_add;
    array_of_freed_areas_t array_list;
    int array[MAX_STACK_SIZE];
    stack_array_t stack_array;
	char filename [MAX_FILENAME_LEN];
    stack_array.size = 0;
    stack_array.ptr = array - 1;
	array_list.size = 0;
	array_list.array = NULL;

    elem_stack_list_t *elem_stack_list = NULL;

    //1 - массив, 2 - список

    rc = menu(&choice);
    if (rc)
    {
        print_error(rc);
        return INCORRECT_CHOICE;
    }
    while (choice != 0)
    {
		if (choice == 1)
		{
			rc = read_cnt_add_stack_arr(&num_add, stack_array.size);

            if (rc)
                return rc;
            if (stack_array.size < MAX_STACK_SIZE)
            {
                rc = add_elem_to_stack_array(&stack_array, num_add);
                if (rc)
                	return rc;
            }
            rc = read_cnt_add_to_stack_list(&num_add, elem_stack_list);

            if (rc)
            {
                print_error(rc);
                free_stack_list(&elem_stack_list);
                free(array_list.array);
                return rc;
            }
            
            if ((elem_stack_list != NULL && elem_stack_list->num_elem != MAX_STACK_SIZE) ||
                 elem_stack_list == NULL)
            {
                rc = add_elem_to_stack_list(&elem_stack_list, num_add, &array_list);
                if (rc)
                {
                    print_error(rc);
                    return rc;
                }
            }
		}
    	if (choice == 2)
    	{
    		rc = read_stack_list_file(&elem_stack_list, &num_add, filename, &array_list);
            if (rc)
            {
                print_error(rc);
                free_stack_list(&elem_stack_list);
                free(array_list.array);
                return rc;
            }
            printf("\n^List\n");
            rc = read_stack_arr_file(&stack_array, &num_add, stack_array.size, filename);
            if (rc)
            {
                print_error(rc);
                return rc;
            }
            printf("\n^Array\n");
    	}
        if (choice == 3)
        {   
            int num_del;
            rc = read_number_of_remove_elem_from_stack_array(&num_del, stack_array.size);
			
            if (rc)
            {
                print_error(rc);
                return rc;
            }

            if (stack_array.size != 0)
                remove_elem_from_stack_array(&stack_array, num_del);

			printf("\n^Array\n");
            printf("\n");
            
            rc = read_number_of_remove_elem_from_stack_list(&num_del, elem_stack_list);
            if (rc)
            {
                print_error(rc);
                free_stack_list(&elem_stack_list);
                free(array_list.array);
                return rc;
            }
            
            if (elem_stack_list != NULL)
            {
                rc = add_addresses_of_removed_elem_to_array(&array_list, num_del, elem_stack_list);

                if (rc)
                {
                    print_error(rc);
                    free_stack_list(&elem_stack_list);
                    return rc;
                }
                remove_elem_from_stack_list(&elem_stack_list, num_del);
            }
			
			printf("\n^List\n");
        }
        else if (choice == 4)
        {
            print_stack_array(&stack_array);
            printf("\n^Array\n");
            print_stack_list(&elem_stack_list);
            printf("\n^List\n");
        }
        else if (choice == 5)
        {
            FILE *f = fopen("out.txt", "w");

            if (!f)
            {
                printf("Не удалось открыть файл\n");
                free_stack_list(&elem_stack_list);
                return FILE_NOT_FOUND;
            }

            print_descend_sequen_stack_array(stack_array, f);
            printf("\n");
            print_descend_sequen_stack_list(elem_stack_list, f);
            fclose(f);
        }
        else if (choice == 0)
        {
            free_stack_list(&elem_stack_list);
            break;
        }
        rc = menu(&choice);
        if (rc)
        {
            printf("%d", choice);
            return INCORRECT_CHOICE;
        }
    }
    return EXIT_SUCCESS;
}
