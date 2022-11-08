#include "constants.h"
#include "structs.h"

int read_stack_type(int *stack_type)
{
    printf("Введите число (1 или 2), чтобы выбрать тип стека:\n"
           "    1 - - стек, реализованный массивом;\n"
           "    2 - - стек, реализонанный списком;\n"
           "Введите 3 для сравнения работы по времени и памяти двух типов стеков\n\n");

    if (scanf("%d", stack_type) != 1 || *stack_type < 1 || *stack_type > 3)
        return INCORRECT_CHOICE;

    return EXIT_SUCCESS;
}

int read_cnt_add_stack_arr(int *num_add, int size)
{
    if (size == MAX_STACK_SIZE)
        return STACK_IS_FULL;

    printf("Введите кол-во добавляемых элементов (не более %d):\n", MAX_STACK_SIZE - size);
    if (scanf("%d", num_add) != 1 || *num_add < 0 || size + (*num_add) > MAX_STACK_SIZE)
        return INCORRECT_DATA;

    return EXIT_SUCCESS;
}

int read_stack_arr_file(stack_array_t *stack_array, int *num_add, int size, char *filename)
{
    if (size == MAX_STACK_SIZE)
        return STACK_IS_FULL;

    printf("Введите название файла, (кол-во добавляемых элементов не более %d)\n", MAX_STACK_SIZE - size);
    if (!fgets(filename, MAX_FILENAME_LEN, stdin))
    {
    	//printf("|%s|",filename);
        return INCORRECT_FILENAME;
	}
    int len = strlen(filename);
    if (filename[len - 1] == '\n')
   	{
        filename[--len] = '\0';
    }
	//printf("|%s|",filename);
    if (len > MAX_FILENAME_LEN - 1)
        return INCORRECT_FILENAME;
    
    FILE *f_in = fopen(filename, "r");
    if (f_in == NULL || feof(f_in))
        return INCORRECT_FILENAME;
    
    if (fscanf(f_in, "%d", num_add) != 1)
        return INCORRECT_DATA;
    
    if (size == MAX_STACK_SIZE)
        return STACK_IS_FULL;
    
    for (int i = 0; i < num_add; i++)
    {
        stack_array->ptr++;
        if (fscanf(f_in, "%d", stack_array->ptr) != 1)
            return INCORRECT_DATA;

        stack_array->size++;
    }
    fclose(f_in);
    return EXIT_SUCCESS;
}

int read_cnt_del_stack_arr(int *num_del, int size)
{
    if (size == 0)
        return STACK_EMPTY;

    printf("Введите кол-во удаляемых элементов (не более %d): ", size);
    if (scanf("%d", num_del) != 1 || *num_del < 0 || size < (*num_del))
        return INCORRECT_DATA;

    return EXIT_SUCCESS;
}

void print_stack_array(stack_array_t *stack_array)
{
    printf("Текущий размер стека - %d\n\n", stack_array->size);

    int *p = stack_array->ptr;

    for (int i = stack_array->size; i > 0; i--)
    {
        printf("%d\n", *(p--));
    }
}

int read_cnt_add_to_stack_list(int *num_add, elem_stack_list_t *elem_stack_list)
{
    if (elem_stack_list != NULL && elem_stack_list->num_elem == MAX_STACK_SIZE)
        return STACK_IS_FULL;

    if (elem_stack_list != NULL)
        printf("Введите кол-во добавляемых элементов (не более %d): ", 
        MAX_STACK_SIZE - elem_stack_list->num_elem);
    else
        printf("Введите кол-во добавляемых элементов (не более 10000): ");

    if (scanf("%d", num_add) != 1 || *num_add < 0)
        return INCORRECT_DATA;

    if (elem_stack_list == NULL)
    {
        if (*num_add > MAX_STACK_SIZE)
            return STACK_OVERFLOW;
    }
    else if (elem_stack_list->num_elem + *num_add > MAX_STACK_SIZE)
        return STACK_OVERFLOW;
    return EXIT_SUCCESS;
}

int read_stack_list_file(elem_stack_list_t *elem_stack_list, int *num_add, int size, char *filename)
{
    if (elem_stack_list != NULL && elem_stack_list->num_elem == MAX_STACK_SIZE)
        return STACK_IS_FULL;

    if (elem_stack_list != NULL)
        printf("Введите название файла (кол-во добавляемых элементов не более %d): ", 
        MAX_STACK_SIZE - elem_stack_list->num_elem);
    else
        printf("Введите название файла (кол-во добавляемых элементов не более 10000): ");
    
    if (!fgets(filename, MAX_FILENAME_LEN, stdin))
    {
    	//printf("|%s|",filename);
        return INCORRECT_FILENAME;
	}
    int len = strlen(filename);
    if (filename[len - 1] == '\n')
   	{
        filename[--len] = '\0';
    }
	//printf("|%s|",filename);
    if (len > MAX_FILENAME_LEN - 1)
        return INCORRECT_FILENAME;
    
    FILE *f_in = fopen(filename, "r");
    if (f_in == NULL || feof(f_in))
        return INCORRECT_FILENAME;
    
    if (fscanf(f_in, "%d", num_add) != 1)
        return INCORRECT_DATA;
    
    if (elem_stack_list == NULL)
    {
        if (*num_add > MAX_STACK_SIZE)
            return STACK_OVERFLOW;
    }
    else if (elem_stack_list->num_elem + *num_add > MAX_STACK_SIZE)
        return STACK_OVERFLOW;
    
    if ((elem_stack_list != NULL && elem_stack_list->num_elem != MAX_STACK_SIZE) || elem_stack_list == NULL)
    {
        elem_stack_list_t *new_elem;

        for (int i = 0; i < num_add; i++)
        {
            new_elem = malloc(sizeof(elem_stack_list_t));

            if (!new_elem)
                return MEMORY_ERROR;

            if (fscanf(f_in, "%d", new_elem->elem) != 1)
                return INCORRECT_DATA;

            if (elem_stack_list == NULL)
                new_elem->num_elem = 1;
            else
                new_elem->num_elem = elem_stack_list->num_elem + 1;
            
            new_elem->next = elem_stack_list;
            elem_stack_list = new_elem;
        }
    }
    else
        return EXIT_FAILURE;
    
    fclose(f_in);
    return EXIT_SUCCESS;
}

int read_number_of_remove_elem_from_stack_list(int *num_del, elem_stack_list_t *elem_stack_list)
{
    if (elem_stack_list == NULL)
        return STACK_EMPTY;

    printf("Введите кол-во удаляемых элементов (не более %d): ", elem_stack_list->num_elem);

    if (scanf("%d", num_del) != 1 || *num_del < 0 || *num_del > elem_stack_list->num_elem)
        return INCORRECT_DATA;
    return EXIT_SUCCESS;
}

void print_stack_list(elem_stack_list_t **elem_stack_list)
{
    if (*elem_stack_list == NULL)
        printf("Текущий размер стека - 0\n\n");
    else
    {
        printf("Текущий размер стека - %d\n\n", (*elem_stack_list)->num_elem);
    
        elem_stack_list_t *p = *elem_stack_list;

        while (p != NULL)
        {
            printf("%-10d %p\n", p->elem, p);
            p = p->next;
        }
    }
}

void print_array(array_of_freed_areas_t *array)
{
    printf("\nМассив адресов освобождённых элементов стека:\n\n[");

    for (int i = 0; i < array->size; i++)
    {
        printf("%p", array->array[i]);

        if (i != array->size - 1)
            printf(", ");
    }

    printf("]\n");
}