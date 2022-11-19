#include "constants.h"
#include "structs.h"
#include "menu.h"
#include "errors.h"
#include "stackio.h"
#include "measure_time.h"

int add_elem_to_stack_array(stack_array_t *stack_array, int num_add)
{
    printf("Введите %d элемент(a, ов) стека.\n", num_add);
    
    for (int i = 0; i < num_add; i++)
    {
        stack_array->ptr++;
        if (scanf("%d", stack_array->ptr) != 1)
            return INCORRECT_DATA;

        stack_array->size++;
    }
    return EXIT_SUCCESS;
}

void remove_elem_from_stack_array(stack_array_t *stack_array, int num_del)
{
    int64_t start = 0, end = 0;
    start+=tick();
    for (int i = 0; i < num_del; i++)
    {
        stack_array->ptr--;
        stack_array->size--;
    }
    end+=tick();
    print_time(start, end);
    printf("%d элемент(а, ов) успешно удалено из стека.\n", num_del);
}

int print_descend_sequen_stack_array(stack_array_t stack_array, FILE *f)
{
    int64_t start = 0, end = 0;
    if (stack_array.size == 0)
    {
        fprintf(f, "Стек пуст.\n");
        return STACK_EMPTY_FILE;
    }

    fprintf(f, "Убывающие серии последовательности целых чисел в обратном порядке "
           "(каждая серия на отдельной строке):\n\n");
    
    int prev_elem;
    prev_elem = *stack_array.ptr;
    stack_array.ptr--;
    int found = 0;
    start+=tick();
    while (stack_array.size > 0)
    {
    	if (*stack_array.ptr > prev_elem)
    	{
    		fprintf(f, "%d ", prev_elem);
    		found = 1;
    	}
		else if (found)
		{
			fprintf(f, "%d\n ", prev_elem);
			found = 0;
		}
		
    	prev_elem = *stack_array.ptr;
    	stack_array.ptr--;
    	stack_array.size--;
    }
    end+=tick();
    print_time(start, end);
   	return EXIT_SUCCESS;
}

void fill_stack_array_randomly(stack_array_t *stack_array, int numb_add_elem)
{
    srand(time(NULL));

    for (int i = 0; i < numb_add_elem; i++)
    {
        stack_array->ptr++;
        stack_array->size++;

        *stack_array->ptr = MIN_BORDER + rand() % (MAX_BORDER - MIN_BORDER + 1);
    }
}

int work_with_stack_array(void)
{
    int choice, rc, num_add, num_del;
    int array[MAX_STACK_SIZE];
    stack_array_t stack_array;
    char filename[MAX_FILENAME_LEN];

    stack_array.size = 0;
    stack_array.ptr = array - 1;

    rc = menu(&choice);
    if (rc)
    {
		printf("%d", choice);
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
            
        }
        else if (choice == 2)
        {
            rc = read_stack_arr_file(&stack_array, &num_add, stack_array.size, filename);
            if (rc)
            {
                print_error(rc);
                return rc;
            }
        }
        else if (choice == 3)
        {
            rc = read_number_of_remove_elem_from_stack_array(&num_del, stack_array.size);

            if (rc)
            {
                print_error(rc);
                return rc;
            }

            if (stack_array.size != 0)
                remove_elem_from_stack_array(&stack_array, num_del);
        }
        else if (choice == 4)
        {
            print_stack_array(&stack_array);
        }
        else if (choice == 5)
        {
            print_descend_sequen_stack_array(stack_array, stdout);
        }
        else if (choice == 0)
            return EXIT_SUCCESS;
        
        rc = menu(&choice);
        if (rc)
        {
            printf("%d", choice);
            return INCORRECT_CHOICE;
        }
    }
    return EXIT_SUCCESS;
}


