#include "constants.h"

void print_error(int rc)
{
    switch (rc)
    {
        case EXIT_FAILURE:
            printf("\nОШИБКА! Введенно неправильное значение.");
            break;
        case DATA_EMPTY_ERR:
            printf("\nОШИБКА! Данные пусты!\n");
            break;
        case FILE_NOT_FOUND:
            printf("\nОШИБКА! ФАЙЛ не найден\n");
            break;
        case MAIN_STRING_OVERFLOW:
            printf("\nОШИБКА! ФАЙЛ - одна из строк переполнена\n");
            break;
        case INCORRECT_CHOICE:
            printf("\nОШИБКА! Некорректный выбор в меню.\n");
            break;
        case INCORRECT_FILENAME:
            printf("\nОШИБКА! Некорректно задано имя файла.\n");
            break;
        case STACK_IS_FULL:
            printf("\nОШИБКА! Стек заполнен.\n");
            break;
        case STACK_EMPTY:
            printf("\nОШИБКА! Стек пуст.\n");
            break;
        case STACK_EMPTY_FILE:
            break;
        case INCORRECT_DATA:
        	printf("ОШИБКА! Некорректные данные!\n");
        	break;
    }
}
