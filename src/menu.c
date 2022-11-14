#include "constants.h"
#include "errors.h"

void print_menu(void)
{
	printf("\nМеню взаимодействия:\n\t"
        "1 - Добавить элементы в стек (из консоли)\n\t"
        "2 - Добавить элементы в стек (из файла)\n\t"
        "3 - Удалить элементы из стека\n\t"
        "4 - Вывести текущее состояние стека\n\t"
        "5 - Распечатать убывающие серии последовательности целых чисел в обратном порядке\n\t"
        "0 - Завершить выполнение программы\n");
}


int menu(int *choice)
{
    *choice = -1;

    if (*choice != 0)
    {
    	print_menu();
    	
    	if (scanf("%d", choice) != 1)
            return INCORRECT_CHOICE;

    	if (*choice < 0 || *choice > 5)
            return INCORRECT_CHOICE;
    }
    return EXIT_SUCCESS;
}
