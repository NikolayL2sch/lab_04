#include "constants.h"
#include "structs.h"
#include "menu.h"
#include "errors.h"
#include "stackio.h"
#include "measure_time.h"

void free_stack_list(elem_stack_list_t **elem_stack_list)
{
    elem_stack_list_t *p;

    while (*elem_stack_list != NULL)
    {
        p = (*elem_stack_list)->next;

        free(*elem_stack_list);
        *elem_stack_list = p;
    }
}

int add_elem_to_stack_list(elem_stack_list_t **elem_stack_list, int num_add, array_of_freed_areas_t *array)
{
    elem_stack_list_t *new_elem;
	
    printf("Введите %d элемент(a, ов) стека.\n", num_add);

    for (int i = 0; i < num_add; i++)
    {
        new_elem = malloc(sizeof(elem_stack_list_t));

        if (!new_elem)
            return MEMORY_ERROR;

        if (scanf("%d", &new_elem->elem) != 1)
        {
            free(new_elem);
            return INCORRECT_DATA;
        }

        if (*elem_stack_list == NULL)
            new_elem->num_elem = 1;
        else
            new_elem->num_elem = (*elem_stack_list)->num_elem + 1;
        
        new_elem->next = *elem_stack_list;
        *elem_stack_list = new_elem;
        if (array->size != 0)
            array->size--;
    }
    return EXIT_SUCCESS;
}

int add_addresses_of_removed_elem_to_array(array_of_freed_areas_t *array, int num_del, elem_stack_list_t *elem_stack_list)
{
    elem_stack_list_t **p;

    for (int i = 0; i < num_del; i++)
    {
        p = realloc(array->array, (array->size + 1) * sizeof(elem_stack_list_t*));
		if (p == NULL)
			printf("why tho");
        if (!p)
        {
            free(array->array);
            printf("Не удалось выделить память\n");
            return STACK_EMPTY_FILE;
        }

        array->array = p;
        array->array[array->size] = elem_stack_list;
        array->size++;
        elem_stack_list = elem_stack_list->next;
    }

    return EXIT_SUCCESS;
}

void remove_elem_from_stack_list(elem_stack_list_t **elem_stack_list, int num_del)
{
    elem_stack_list_t *new_elem;

    for (int i = 0; i < num_del; i++)
    {
        new_elem = (*elem_stack_list)->next;
        free(*elem_stack_list);
        *elem_stack_list = new_elem;
    }

    printf("%d элемент(а, ов) успешно удалено из стека.\n", num_del);
}

void print_descend_sequen_stack_list(elem_stack_list_t *elem_stack_list, FILE *f)
{
    if (elem_stack_list == NULL)
    {
        fprintf(f, "Стек пуст.\n");
        return;
    }

    fprintf(f, "Убывающие серии последовательности целых чисел в обратном порядке "
           "(каждая серия на отдельной строке):\n\n");
    
    int prev_elem, k;

    while (elem_stack_list != NULL && elem_stack_list->next != NULL)
    {
        prev_elem = elem_stack_list->elem;
        k = 0;

        elem_stack_list = elem_stack_list->next;

        while (elem_stack_list != NULL &&
               elem_stack_list->elem > prev_elem)
        {
            fprintf(f, "%d ", prev_elem);

            prev_elem = elem_stack_list->elem;
            elem_stack_list = elem_stack_list->next;
            k = 1;
        }

        if (k == 1)
            fprintf(f, "%d\n", prev_elem);
    }
}

int fill_stack_list_randomly(elem_stack_list_t **elem_stack_list, int numb_add_elem)
{
    elem_stack_list_t *new_elem;

    srand(time(NULL));

    for (int i = 0; i < numb_add_elem; i++)
    {
        new_elem = malloc(sizeof(elem_stack_list_t));

        if (!new_elem)
            return MEMORY_ERROR;

        new_elem->elem = MIN_BORDER + rand() % (MAX_BORDER - MIN_BORDER + 1);

        if (*elem_stack_list == NULL)
            new_elem->num_elem = 1;
        else
            new_elem->num_elem = (*elem_stack_list)->num_elem + 1;
        
        new_elem->next = *elem_stack_list;
        *elem_stack_list = new_elem;
    }

    return EXIT_SUCCESS;
}

int work_with_stack_list(void)
{
    int choice, rc, num_add, num_del;
    elem_stack_list_t *elem_stack_list = NULL;
    array_of_freed_areas_t array;
    char filename[MAX_FILENAME_LEN];
    array.array = NULL;
    array.size = 0;

    rc = menu(&choice);
    if (rc)
    {
        free_stack_list(&elem_stack_list);
        free(array.array);
        print_error(rc);
        return INCORRECT_CHOICE;
    }
    while (choice != 0)
    {
        if (choice == 1)
        {   
            rc = read_cnt_add_to_stack_list(&num_add, elem_stack_list);

            if (rc)
            {
                print_error(rc);
                free_stack_list(&elem_stack_list);
                free(array.array);
                return rc;
            }
            
            if ((elem_stack_list != NULL && elem_stack_list->num_elem != MAX_STACK_SIZE) ||
                 elem_stack_list == NULL)
            {
                rc = add_elem_to_stack_list(&elem_stack_list, num_add, &array);
                if (rc)
                {
                    print_error(rc);
                    return rc;
                }
            }
        }
        else if (choice == 2)
        {
            rc = read_stack_list_file(&elem_stack_list, &num_add, filename, &array);
            if (rc)
            {
                print_error(rc);
                free_stack_list(&elem_stack_list);
                free(array.array);
                return rc;
            }
        }
        else if (choice == 3)
        {
            rc = read_number_of_remove_elem_from_stack_list(&num_del, elem_stack_list);

            if (rc)
            {
                print_error(rc);
                free_stack_list(&elem_stack_list);
                free(array.array);
                return rc;
            }

            if (elem_stack_list != NULL)
            {
                rc = add_addresses_of_removed_elem_to_array(&array, num_del, elem_stack_list);

                if (rc)
                {
                    print_error(rc);
                    free_stack_list(&elem_stack_list);
                    return rc;
                }

                remove_elem_from_stack_list(&elem_stack_list, num_del);
            }
        }
        else if (choice == 4)
        {
            print_stack_list(&elem_stack_list);
            print_array(&array);
        }
        else if (choice == 5)
        {
            print_descend_sequen_stack_list(elem_stack_list, stdout);
        }
        else if (choice == 0)
        {
            free_stack_list(&elem_stack_list);
            free(array.array);
            return EXIT_SUCCESS;
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
