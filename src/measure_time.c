#include "constants.h"
#include "structs.h"

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
    printf("%lld тактов, %.10lf секунд\n", end - start, (double)(end - start)/GHZ);  
}

int compare_stacks(void)
{
    int choice, rc;
    int array[MAX_STACK_SIZE];
    stack_array_t stack_array;

    stack_array.size = 0;
    stack_array.ptr = array - 1;

    elem_stack_list_t *elem_stack_list = NULL;
    
    int64_t start = 0, end = 0;

    //1 - массив, 2 - список

    rc = menu(&choice);
    if (rc)
    {
        print_error(rc);
        return INCORRECT_CHOICE;
    }
    while (choice != 0)
    {
        if (choice == 3)
        {   
           int num_del;
            rc = read_cnt_del_stack_arr(&num_del, stack_array.size);

            if (rc)
            {  
                print_error(rc);
                free_stack_list(&elem_stack_list);
                return rc;
            }

            printf("\n");

            if (stack_array.size != 0)
            {
                for (int i = 0; i < NUMBER_OF_RUNS; i++)
                {
                    start += tick();
                    remove_elem_from_stack_array(&stack_array, num_del);
                    end += tick();

                    fill_stack_array_randomly(&stack_array, num_del);
                }
                
                remove_elem_from_stack_array(&stack_array, num_del);

                print_result(start / NUMBER_OF_RUNS, end / NUMBER_OF_RUNS);

                start = 0;
                end = 0;

                printf("\n");
                
                for (int i = 0; i < NUMBER_OF_RUNS; i++)
                {
                    start += tick();
                    remove_elem_from_stack_list(&elem_stack_list, num_del);
                    end += tick();

                    fill_stack_list_randomly(&elem_stack_list, num_del);
                }

                remove_elem_from_stack_list(&elem_stack_list, num_del);

                print_result(start / NUMBER_OF_RUNS, end / NUMBER_OF_RUNS);

                start = 0;
                end = 0;
            }
        }
        else if (choice == 4)
        {
            print_stack_array(&stack_array);
            printf("\n");
            print_stack_list(&elem_stack_list);
        }
        else if (choice == 5)
        {
            FILE *f = fopen("out.txt", "w+");

            if (!f)
            {
                printf("Не удалось открыть файл\n");
                free_stack_list(&elem_stack_list);
                return FILE_NOT_FOUND;
            }

            for (int i = 0; i < NUMBER_OF_RUNS; i++)
            {
                start += tick();
                print_descend_sequen_stack_array(stack_array, f);
                end += tick();
            }
        
            print_result(start / NUMBER_OF_RUNS, end / NUMBER_OF_RUNS);

            start = 0;
            end = 0;

            printf("\n");

            for (int i = 0; i < NUMBER_OF_RUNS; i++)
            {
                start += tick();
                print_descend_sequen_stack_list(elem_stack_list, f);
                end += tick();
            }

            print_result(start / NUMBER_OF_RUNS, end / NUMBER_OF_RUNS);

            start = 0;
            end = 0;

            // print_descend_sequen_stack_array(stack_array, stdout);
            // printf("\n");
            // print_descend_sequen_stack_list(elem_stack_list, stdout);
        }
        else if (choice == 0)
        {
            free_stack_list(&elem_stack_list);
            break;
        }       
    }
    return EXIT_SUCCESS;
}